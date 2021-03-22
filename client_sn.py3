import socket

#localhost in IPv4 interface
HOST = '3.139.59.213'
#int with port number from 1-65535
PORT = 8080

#arguments passed to socket() specify the address family and socket type
#AF_INET is the Internet address family for IPv4.
#SOCK_STREAM is the socket type for TCP (protocol that will be used)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
state = int(input("Input 1 to start process: "))

s.connect((HOST, PORT))

while(state==1):
    msg = input("Input message you would like to send: ")
    s.send(bytes(msg,"utf-8"))
    #recieve the stream of data and decide how big of chunks of data want to recieve at a time
    #msg = s.recv(65532)
    #print(msg.decode("utf-8"))
    state = int(input("Type 1 to send another message, else type ANYTHING: "))
