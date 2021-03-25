import subprocess
import time
import socket
import threading
import sys
import errno
import fcntl, os

def process_directions(x, y):
    radius = 50
    if abs(x) > abs(y) and abs(x) > radius:
	    if x > 0:
	        return "a" # move left
	    else:
	        return "d" # move right
    elif abs(y) > radius:
	    if y > 0:
		    return "s" # move down
	    else:
		    return "w" # move up
    else:
	    return "q" # no movement

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

    # Returns the current x coordinate
    x = vals[1].strip()
    # print ("x captured")
    if x == "e"  :
    #    print("shooting")
        return x
    elif x == "r" :
    #    print("bombing")
        return x
    else :
        y = vals[3].strip()
        return process_directions(int(x), int(y))
    # Returns the current y coordinate
    #y = vals[3].strip()

    # print(vals[4].strip())

    # To store past values, pass a vector or something which
    #   is continually updated with the previous x and y values

    #output_char = process_directions(int(x), int(y))

def main():

        # Testing NIOS II to Ecplise by just printing to the terminal
    # cmd - variable we send to eclipse
    # msg - variable we receive from eclipse

    cmd = 's'
    #while 1:
    #    send_on_jtag(cmd)

        # ---------- Receiving info from the server ----------
    # while there is not a character being received from the server, just send an 's'

        # ------------------ SALMAN'S CODE -------------------
        # Sending information to the server
    #localhost in IPv4 interface
    HOST = '52.56.73.213'
    #int with port number from 1-65535
    PORT = 8080

    #arguments passed to socket() specify the address family and socket type
    #AF_INET is the Internet address family for IPv4.
    #SOCK_STREAM is the socket type for TCP (protocol that will be used)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


    word = "Player"
    s.connect((HOST, PORT))
    # s.send(bytes(word,"utf-8"))

    initial_cmd = s.recv(128)
    print(initial_cmd.decode("utf-8"))

    s.send(bytes(word,"utf-8"))

    s.setblocking(0)
    while True:
        # Grab the output character from the NIOS II terminal
        msg = send_on_jtag(cmd)
        cmd = 's'
        s.send(bytes(msg,"utf-8"))
        try:    # try to receive a character from the stream
            cmd = s.recv(128)
            cmd = cmd.decode()
            # if nothing is received, run the 'except' bit to not abort
        except socket.error as e:
            err = e.args[0]
            if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                continue # continue if you get an expected error
            else:
                # a unexpected error occurred
                sys.exit(1)

    s.close()

if __name__ == '__main__':
    main()
