import socket

#localhost in IPv4 interface
HOST = '3.95.175.51'
#int with port number from 1-65535
PORT = 8080

#arguments passed to socket() specify the address family and socket type
#AF_INET is the Internet address family for IPv4.
#SOCK_STREAM is the socket type for TCP (protocol that will be used)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
state = input()

if state ==1 :
    s.connect((HOST, PORT))

while (state==1):
    #recieve the stream of data and decide how big of chunks of data want to recieve at a time
    msg = s.recv(65532)
    print(msg.decode("utf-8"))
    #s.close()
    state = input()
