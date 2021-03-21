import subprocess
import time
import socket

def process_directions(x, y):
    radius = 50
    if abs(x) > abs(y) and abs(x) > radius:
	    if x > 0:
	        return "j"
	    else:
	        return "l"
    elif abs(y) > radius:
	    if y > 0:
		    return "k"
	    else:
		    return "i"
    else:
	    return "q"

# Function used to send information to the board.
# This function takes an input character which is passed into the
#   .c file in Eclipse.
def send_on_jtag(cmd):
    # assert len(cmd)==1, "Please make the cmd a single character"

    inputCmd = 'nios2-terminal.exe <<< {}'.format(cmd);
    
    output = subprocess.run(inputCmd, shell=True, executable='/bin/bash', stdout=subprocess.PIPE)
        
    vals = output.stdout
    vals = vals.decode("utf-8")
    vals = vals.split('<-->')
    # Used to handle outputs other than coordinates
    # vals2 = vals.split('<||>')

    # Returns the current x coordinate
    x = vals[1].strip()
    # Returns the current y coordinate
    y = vals[3].strip()

    // print(vals[4].strip())

    # To store past values, pass a vector or something which
    #   is continually updated with the previous x and y values

    print(process_directions(int(x), int(y)))
    

def main():

    cmd = 'z'
    while 1:
        send_on_jtag(cmd)
        # SALMAN'S CODE
    #localhost in IPv4 interface
    HOST = '52.56.73.213'
    #int with port number from 1-65535
    PORT = 8080

    #arguments passed to socket() specify the address family and socket type
    #AF_INET is the Internet address family for IPv4.
    #SOCK_STREAM is the socket type for TCP (protocol that will be used)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    state = 1
    # int(input("Input 1 to start process: "))
    #   Can use this to commence the game

    s.connect((HOST, PORT))

    while(state==1):
        msg = send_on_jtag(cmd)
        #input("Input message you would like to send: ")
        s.send(bytes(msg,"utf-8"))
        #recieve the stream of data and decide how big of chunks of data want to recieve at a time
        #msg = s.recv(65532)
        #print(msg.decode("utf-8"))
        # state = int(input("Type 1 to send another message, else type ANYTHING: "))
    
    s.close()

if __name__ == '__main__':
    main()
