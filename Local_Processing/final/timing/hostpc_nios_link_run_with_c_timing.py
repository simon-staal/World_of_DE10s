import subprocess
import time
import socket
import threading
import sys
import errno
import fcntl, os

#           ---  Local direction processing function ---
#   This function reads the current x and y axis values read out from the NIOS II 
#   processor and outputs the corresponding direction denoted by wasd as a single character. 
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

#           --- Information transfer to NIOS II function ---
#   This function takes an input character and sends it to the NIOS II terminal. It then reads
#   the reply printed to the NIOS II terminal and handles the relevant data.
def send_on_jtag(cmd):
    # print(cmd)
    # assert len(cmd)==1, "Please make the cmd a single character"

    # command we will run to send information to the NIOS II terminal
    inputCmd = 'nios2-terminal.exe <<< {}'.format(cmd);

    # running the command and capturing the result from the NIOS II terminal in the variable output
    output = subprocess.run(inputCmd, shell=True, executable='/bin/bash', stdout=subprocess.PIPE)

    # decoding and removing suffixes/prefixes from the NIOS II output
    vals = output.stdout
    vals = vals.decode("utf-8")
    vals = vals.split('<-->')

        #   Output capturing
    # vals[1].strip() indicates the first output from the NIOS II terminal and is stored in x
    # x = vals[1].strip()

    i = 1
    # print(vals[0].strip())

    while vals[i].strip() != "END":
        print(vals[i].strip())
        i+=1

        #   Output processing
    # if x is the letter 'e', KEY0 / the top button is being pushed therefore telling the 
    # player's tank to shoot it's bullets
    # if x == "e"  :
    # #    print("shooting")
    #     return x
    # # if x is the letter 'r', KEY1 / the bottom button is bieng pushed therefore telling the
    # # player's tank to drop it's bomb
    # elif x == "r" :
    # #    print("bombing")
    #     return x
    # else :
    #     # if the first character is neither of these, we have received an x-coordinate value
    #     # and we know that the output value in the 3rd index is the y-axis value.
    #     y = vals[3].strip()
    #     # send the received information to the process_directions function
    #     return process_directions(int(x), int(y))


def main():

    print("sending an s")
    send_on_jtag('s')
    print("=======================")
    print("sending an n")
    send_on_jtag('n')
    print("=======================")
    print("sending an r")
    send_on_jtag('r')
    print("=======================")
    print("sending an l")
    send_on_jtag('l')
    print("=======================")
    print("sending a w")
    send_on_jtag('w')


        # Testing NIOS II to Ecplise by just printing to the terminal
    # cmd - variable we send to eclipse
    # msg - variable we receive from eclipse

    #           --- Establishing a connection with the server ---
    # localhost in IPv4 interface
    # HOST = '52.56.78.234'
    # # int with port number from 1-65535
    # PORT = 6969

    # # arguments passed to socket() specify the address family and socket type
    # # AF_INET is the Internet address family for IPv4.
    # # SOCK_STREAM is the socket type for TCP (protocol that will be used)
    # s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # # establish connection with the server
    # s.connect((HOST, PORT))

    # # The connection with the server must be initialised by receiving information
    # # then sending (the same or different) information back
    
    # # Receiving the initial word/information
    # initial_cmd = s.recv(128)
    # print(initial_cmd.decode("utf-8"))

    # # Sending the response word/information
    # word = "Player"
    # s.send(bytes(word,"utf-8"))

    # second_cmd = s.recv(128)
    # print(second_cmd.decode("utf-8"))

    # # Make socket non-blocking 
    # # Allows send and recv to return without having done anything
    # s.setblocking(0)

    # #           --- Connecting the stream of information from the server to NIOS II ---
    # # This loop reads the received character from the server and uses the send_on_jtag()
    # # function to transmit it to the NIOS II processor

    # #       --- Variables and their uses ---
    # #   cmd - character we will be sending to the NIOS II processor
    # # Initialise the character cmd with the letter 's'
    # cmd = 's'
    # #   msg - character being received from the NIOS II processor
    # # This variable is initialised with the first return value of send_ont_jtag(cmd)

    # while True:
    #     # Grab the output character from the NIOS II terminal
    #     msg = send_on_jtag(cmd)
    #     cmd = 's'
    #     # Send the received character to the server
    #     s.send(bytes(msg,"utf-8"))
    #     try:    # try to receive a character from the stream
    #         cmd = s.recv(128)
    #         cmd = cmd.decode()
    #         # if nothing is received, run the 'except' bit to not abort
    #     except socket.error as e:
    #         err = e.args[0]
    #         if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
    #             continue # can continue if you get an expected error
    #         else:
    #             # a unexpected error occurred
    #             sys.exit(1)

    # s.close()

if __name__ == '__main__':
    main()
