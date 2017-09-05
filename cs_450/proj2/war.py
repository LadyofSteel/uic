"""
war card game client and server
"""
import asyncio
from collections import namedtuple
from enum import Enum
import logging
import random
import socket
import socketserver
import threading
import sys
import struct

"""
Namedtuples work like classes, but are much more lightweight so they end
up being faster. It would be a good idea to keep objects in each of these
for each game which contain the game's state, for instance things like the
socket, the cards given, the cards still available, etc.
"""
Game = namedtuple("Game", ["p1", "p2"])


class Command(Enum):
    """
    The byte values sent as the first byte of any message in the war protocol.
    """
    WANTGAME = 0
    GAMESTART = 1
    PLAYCARD = 2
    PLAYRESULT = 3


class Result(Enum):
    """
    The byte values sent as the payload byte of a PLAYRESULT message.
    """
    WIN = 0
    DRAW = 1
    LOSE = 2


async def readexactly(sock, numbytes):
    """
    Accumulate exactly `numbytes` from `sock` and return those. If EOF is found
    before numbytes have been received, be sure to account for that here or in
    the caller.
    """
    data = sock.recv(numbytes)
    while (len(data) < numbytes):
        data += sock.recv(numbytes)

    return data


def kill_game(game):
    """
    If either client sends a bad message, immediately nuke the game.
    """
    game[0].close()
    game[1].close()

    return


def compare_cards(card1, card2):
    """
    Given an integer card representation, return -1 for card1 < card2,
    0 for card1 = card2, and 1 for card1 > card2.
    """
    card1 = card1 % 13
    card2 = card2 % 13

    if (card1 < card2):
        return -1
    if (card1 == card2):
        return 0
    if (card1 > card2):
        return 1

    return


def deal_cards():
    """
    Randomize a deck of cards (list of ints 0..51), and return two
    26 card "hands".
    """
    # Shuffle the 52 cards (0->51).
    cards = list(range(52))
    random.shuffle(cards)

    # Pack each half of the deck into byte string to send to players
    # (including GAMESTART byte).
    hand1 = struct.pack('27B', Command.GAMESTART.value, *cards[:26])
    hand2 = struct.pack('27B', Command.GAMESTART.value, *cards[26:])

    return hand1, hand2


def send_results(client1, client2, comparison):
    """
    Given the card comparison value, send the play
    results to both players/clients.
    """
    if (comparison == 0):
        player1Result = struct.pack(
            '2B', Command.PLAYRESULT.value, Result.DRAW.value)
        player2Result = struct.pack(
            '2B', Command.PLAYRESULT.value, Result.DRAW.value)
    elif (comparison == -1):
        player1Result = struct.pack(
            '2B', Command.PLAYRESULT.value, Result.LOSE.value)
        player2Result = struct.pack(
            '2B', Command.PLAYRESULT.value, Result.WIN.value)
    else:
        player1Result = struct.pack(
            '2B', Command.PLAYRESULT.value, Result.WIN.value)
        player2Result = struct.pack(
            '2B', Command.PLAYRESULT.value, Result.LOSE.value)

    try:
        client1.sendall(player1Result)
        client2.sendall(player2Result)
    except socket.error:
        kill_game((client1, client2))
        return

    return


def serve_clients(client1, client2):
    """
    Given the sockets for both players/clients,
    serve them a full game of WAR.

    This function is passed into each new thread
    to allow for more than 2 players playing 
    on the server concurrently.
    """
    buf = 2

    # Listen and wait until both players are ready.
    data1 = client1.recv(buf)
    data2 = client2.recv(buf)

    # If either players sent something wrong, end the game.
    if (data1 != b'\0\0' or data2 != b'\0\0'):
        kill_game((client1, client2))
        return

    # Deal the cards to the two players.
    hand1, hand2 = deal_cards()

    try:
        client1.sendall(hand1)
        client2.sendall(hand2)
    except socket.error:
        logging.error("Error sending cards")
        kill_game((client1, client2))
        return

    numPlays = 1
    # While there are cards left to play
    while (numPlays < 27):
        print("Play number: {}".format(numPlays))

        # Receive 'play card' from clients
        try:
            playCard1 = client1.recv(buf)
            playCard2 = client2.recv(buf)
        except socket.error:
            kill_game((client1, client2))
            return

        # Unpack both messages to get the card values.
        try:
            data1 = struct.unpack('2B', playCard1)
            data2 = struct.unpack('2B', playCard2)
        except:
            kill_game((client1, client2))
            return

        player1Card = data1[1]
        player2Card = data2[1]

        print("Player1 sent: {} \nPlayer2 sent: {}".format(data1, data2))

        # If any command received is not 'play card', end the game.
        if ((data1[0] != Command.PLAYCARD.value) or (data2[0] != Command.PLAYCARD.value)):
            kill_game((client1, client2))
            return

        # Call compare_cards() to compare card values.
        comparison = compare_cards(player1Card, player2Card)

        # Send 'play result' to both clients.
        send_results(client1, client2, comparison)

        numPlays += 1

    return


def serve_game(host, port):
    """
    Open a socket for listening for new connections on host:port, and
    perform the war protocol to serve a game of war between each client.
    This function should run forever, continually serving clients.
    """
    # Set up two sockets for clients
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error:
        print("Failed to create socket")
        sys.exit()
    print("Socket created!")

    # Bind socket and listen for connections
    s.bind((host, port))
    s.listen()

    while 1:
        # Accept two client connections
        sock1, addr1 = s.accept()
        print("First client accepted!")
        sock2, addr2 = s.accept()
        print("Second client accepted!")

        # Spawn new thread with the two sockets/clients
        # and pass in the function 'serve_clients'
        newThread = threading.Thread(
            target=serve_clients, args=(sock1, sock2,))
        newThread.start()

    return

async def limit_client(host, port, loop, sem):
    """
    Limit the number of clients currently executing.
    You do not need to change this function.
    """
    async with sem:
        return await client(host, port, loop)

async def client(host, port, loop):
    """
    Run an individual client on a given event loop.
    You do not need to change this function.
    """
    try:
        reader, writer = await asyncio.open_connection(host, port, loop=loop)
        # send want game
        writer.write(b"\0\0")

        print("Sent want game")

        card_msg = await reader.readexactly(27)

        print("Game starting!")

        myscore = 0
        for card in card_msg[1:]:
            writer.write(bytes([Command.PLAYCARD.value, card]))
            result = await reader.readexactly(2)
            if result[1] == Result.WIN.value:
                myscore += 1
            elif result[1] == Result.LOSE.value:
                myscore -= 1
        if myscore > 0:
            result = "won"
        elif myscore < 0:
            result = "lost"
        else:
            result = "drew"
        logging.debug("Game complete, I %s", result)
        writer.close()
        return 1
    except ConnectionResetError:
        logging.error("ConnectionResetError")
        return 0
    except asyncio.streams.IncompleteReadError:
        logging.error("asyncio.streams.IncompleteReadError")
        return 0
    except OSError:
        logging.error("OSError")
        return 0


def main(args):
    """
    launch a client/server
    """
    host = args[1]
    port = int(args[2])
    if args[0] == "server":
        try:
            # Your server should serve clients until the user presses ctrl+c
            serve_game(host, port)
        except KeyboardInterrupt:
            sys.exit()
        return
    else:
        loop = asyncio.get_event_loop()

    if args[0] == "client":
        loop.run_until_complete(client(host, port, loop))
    elif args[0] == "clients":
        sem = asyncio.Semaphore(1000)
        num_clients = int(args[3])
        clients = [limit_client(host, port, loop, sem)
                   for x in range(num_clients)]
        async def run_all_clients():
            """
            use `as_completed` to spawn all clients simultaneously
            and collect their results in arbitrary order.
            """
            completed_clients = 0
            for client_result in asyncio.as_completed(clients):
                completed_clients += await client_result
            return completed_clients
        res = loop.run_until_complete(
            asyncio.Task(run_all_clients(), loop=loop))
        logging.info("%d completed clients", res)

    loop.close()

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    main(sys.argv[1:])
