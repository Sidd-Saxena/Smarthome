import socket
UDP_IP = "192.168.1.102"
UDP_PORT = 1024
 
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
    
while True:
	print "Listening..."
	data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
 	print "received message: ", data
