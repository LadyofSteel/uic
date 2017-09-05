"""
Where solution code to HW5 should be written.  No other files should
be modified.
"""

import signal
import select
import socket
import io
import time
import struct
import homework5
import homework5.logging

HEADER_FMT = 'I'
HEADER_SIZE = struct.calcsize(HEADER_FMT)


def get_timeout(SampleRTT, EstRTT, DevRTT):
    """
    Returns the timeout interval to determine packet 
    transmission timout.

    Function returns tuple of (EstRTT, DevRTT, TimeoutInterval)
    """
    EstRTT = (0.875 * EstRTT) + (0.125 * SampleRTT)
    DevRTT = (0.75 * DevRTT) + (0.25 * abs(SampleRTT - EstRTT))
    TimeoutInterval = EstRTT + (4 * DevRTT)

    return (EstRTT, DevRTT, TimeoutInterval)


def extract_header(packet):
    """
    Given a received packet, extract the header bits and
    return as a tuple of (seqNum, checksum)
    """
    # Unpack the bytes in big-endian
    header = struct.unpack(HEADER_FMT, packet[:HEADER_SIZE])

    return header[0]


def extract_data(packet):
    """
    Given a received packet, extract the data
    and return as bytestring
    """
    data = packet[HEADER_SIZE:]

    return data


def make_ACK(seqNum):
    """
    Given the seqNum, create an ACK packet
    for the receiver to send.
    """
    sndpkt = struct.pack(HEADER_FMT, seqNum)

    return sndpkt


def make_pkt(seqNum, data):
    """
    Given the seqNum and data, create a packet for 
    the sender to send.
    """
    header = struct.pack(HEADER_FMT, seqNum)

    sndpkt = header + data

    return sndpkt


def delete_acked_pkts(buf, seqNum, base):
    """
    Given buffer of in_flight pkts, deletes the
    ACKed packets from seqNum incrementally.
    Returns the new seqNum and base
    """
    i = seqNum
    for key, value in buf.items():
        if key == seqNum:
            if value[0] == 'A':
                value[0] = 'S'
                seqNum += 1
                base += 1
        else:
            break

    while buf.get(i, None) is not None:
        value = buf[i]
        if value[0] == 'S':
            buf.pop(i)
        i += 1
    return seqNum, base


def deliver_data(dest, numBytes, buf, seqNum):
    """
    Given file dest and buffer of on_hold pkts,
    writes the on_hold pkts to dest and returns
    numBytes and new seqNum
    """
    while True:
        try:
            data = buf[seqNum]
            dest.write(data)
            numBytes += len(data)
            dest.flush()
            seqNum += 1
        except KeyError:
            return numBytes, seqNum


def send(sock: socket.socket, data: bytes):
    """
    Implementation of the sending logic for sending data over a slow,
    lossy, constrained network.

    Args:
        sock -- A socket object, constructed and initialized to communicate
                over a simulated lossy network.
        data -- A bytes object, containing the data to send over the network.
    """
    logger = homework5.logging.get_logger("hw5-sender")

    # Initialize the needed RTTs
    timeout = 1
    SampleRTT = 0.1
    EstRTT = 0.75
    DevRTT = 0.1

    base = 0
    cwnd = 5
    lastSeq = 0
    seqNum = 0
    rcvSeq = 0
    numChunks = 0

    in_flight = {}
    packets = []

    def retransmit(*args):
        """
        Signal handler for the timeout signal.
        Retransmits expired, unACKed pkts and resets timer
        """
        for key, value in in_flight.items():
            if value[0] == 'N':
                if time.perf_counter() - value[1] > timeout:
                    sendTime = time.perf_counter()
                    sock.send(packets[key])
                    value[1] = sendTime
        signal.setitimer(signal.ITIMER_REAL, timeout)

    chunkSize = homework5.MAX_PACKET - HEADER_SIZE
    offsets = range(0, len(data), chunkSize)
    chunks = [data[i:i + chunkSize] for i in offsets]

    for chunk in chunks:
        packets.append(make_pkt(seqNum, chunk))
        seqNum += 1
        numChunks += 1
    seqNum = 0

    signal.signal(signal.SIGALRM, retransmit)

    # Start sending pkts in cwnd
    while base + cwnd <= numChunks:
        while lastSeq < base + cwnd:
            sendTime = time.perf_counter()

            sock.send(packets[lastSeq])
            in_flight[lastSeq] = ['N', sendTime]
            lastSeq += 1

        signal.setitimer(signal.ITIMER_REAL, timeout)

        while rcvSeq < lastSeq:
            rcvpkt = sock.recv(homework5.MAX_PACKET)
            if not rcvpkt:
                break

            SampleRTT = time.perf_counter() - sendTime
            EstRTT, DevRTT, timeout = get_timeout(SampleRTT, EstRTT, DevRTT)

            rcvSeq = extract_header(rcvpkt)

            pktTime = in_flight[rcvSeq]
            in_flight[rcvSeq] = ['A', pktTime[1]]

            if rcvSeq == seqNum:
                seqNum, base = delete_acked_pkts(in_flight, seqNum, base)
                break


def recv(sock: socket.socket, dest: io.BufferedIOBase) -> int:
    """
    Implementation of the receiving logic for receiving data over a slow,
    lossy, constrained network.

    Args:
        sock -- A socket object, constructed and initialized to communicate
                over a simulated lossy network.

    Return:
        The number of bytes written to the destination.
    """
    logger = homework5.logging.get_logger("hw5-receiver")

    numBytes = 0
    seqNum = 0

    on_hold = {}

    while True:
        rcvpkt = sock.recv(homework5.MAX_PACKET)
        if not rcvpkt:
            break

        rcvSeq = extract_header(rcvpkt)
        data = extract_data(rcvpkt)
        sock.send(make_ACK(rcvSeq))

        on_hold[rcvSeq] = data

        if rcvSeq == seqNum:
            numBytes, seqNum = deliver_data(dest, numBytes, on_hold, seqNum)
            on_hold.clear()

    return numBytes
