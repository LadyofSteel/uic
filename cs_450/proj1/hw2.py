import logging
import socket
import sys

# Function that checks of the response code is 200 OK
def response_ok(data):

	if data.find(b"200 OK") == -1:
		return False
	else:
		return True

# Function that checks if the transfer is chunk encoded
def chunked_encoding(data):

	if data.find(b"Transfer-Encoding: chunked\r\n") == -1:
		return False
	else:
		return True

# Function that gnereates a GET request from the given path
# and returns the http request string, the host name, and the portnumber
def generate_request(path):

	# Split the path at the first '/' char
	partitions = path.split('/', 1)
	# The host name is whatever was before '/' 
	hostName = partitions[0]

	# If there was no '/' char in the path
	if len(partitions) == 1:
		# The requested path is home ('/')
		requestPath = "/"
	else:
		requestPath = "/" + partitions[1]

	httpRequest = "GET {} HTTP/1.1\r\nHost: {}:{}\r\nConnection: Close\r\n\r\n"

	# If there's no nonstandard port
	# set port number to default (80)
	if hostName.find(":") == -1:
		portNumber = 80
	# Otherwise use the nonstandard port number
	else:
		partitions = hostName.split(":")
		hostName = partitions[0]
		portNumber = int(partitions[1])
		
	# Now format the http request string from what we parsed
	httpRequest = httpRequest.format(requestPath, hostName, portNumber)

	return httpRequest, hostName, portNumber


# Function that parses the chunks from chunk encoded http response
def parse_chunks(data, chunkFlag):

	chunkedData = b""
	while True:
		# Split at first CRLF
		partitions = data.split(b"\r\n", 1)
		# Get the size of chunk in hex
		sizeHex = partitions[0]

		# If it's 0, we reached end of response
		if sizeHex == b'0':
			break
		sizeInt = int(sizeHex, 16)

		# Now we take everything after the split
		chunk = partitions[1]
		# Only consider the data within the given size of chunk
		chunkedData += chunk[:sizeInt]
		# Update the data to parse the rest of the chunks
		data = chunk[sizeInt+2:]

	return chunkedData


# Function that parses the url, sends the appropriate 
# request message, establishes connection with host,
# receives the response from host, then returns the 
# body of the document requested at url
def retrieve_url(url):

	# Partition the url and get the path
	partitions = url.split("http://")
	try:
		fullPath = partitions[1]
	except IndexError:
		return None

	# Generate a request message and get info
	httpRequest, hostName, portNumber = generate_request(fullPath)

	# print (httpRequest)

	# Setup socket for TCP protocol
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# Connect to host using obtained port number
	# return 'None' if host doesn't exist
	try:
		s.connect((bytes(hostName, 'utf-8'), portNumber))
	except socket.error:
		return None

	# Send the generated http request
	s.send(bytes(httpRequest, 'utf-8'))

	# Now receive the response from server
	data = s.recv(4096)

	# Check if response code is 200 OK
	# Otherwise return 'None'
	if not response_ok(data):
		return None

	# Raise a flag if transfer is chunk encoded
	if not chunked_encoding(data):
		chunkFlag = False
	else:
		chunkFlag = True

	newData = data
	# Keep receiving data until end is reached
	while True:
		data = s.recv(4096)
		if not data:
			break
		newData += data

	# Now split the received data
	# Only get the body of the document
	partitions = newData.split(b"\r\n\r\n", 2)
	finalData = partitions[1]

	# Return parsed chunks if transfer is chunk encoded
	# Otherwise return finalData
	if chunkFlag:
		return parse_chunks(finalData, chunkFlag)
	else:
		return finalData


if __name__ == "__main__":
    sys.stdout.buffer.write(retrieve_url(sys.argv[1])) # pylint: disable=no-member
