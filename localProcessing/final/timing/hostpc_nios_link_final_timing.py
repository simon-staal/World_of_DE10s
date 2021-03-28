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
    print(cmd)
    # assert len(cmd)==1, "Please make the cmd a single character"

    # command we will run to send information to the NIOS II terminal
    inputTimeStart = time.perf_counter()
    inputCmd = 'nios2-terminal.exe <<< {}'.format(cmd);
    inputTimeEnd = time.perf_counter()
    inputTimeDif = inputTimeEnd - inputTimeStart
    print("Sending character to NIOS II terminal : ", inputTimeDif, " seconds")

    # running the command and capturing the result from the NIOS II terminal in the variable output
    outputTimeStart = time.perf_counter()
    output = subprocess.run(inputCmd, shell=True, executable='/bin/bash', stdout=subprocess.PIPE)
    outputTimeEnd = time.perf_counter()
    outputTimeDif = outputTimeEnd - outputTimeStart
    print("Retrieving character from NIOS II terminal : ", outputTimeDif, " seconds")

    # decoding and removing suffixes/prefixes from the NIOS II output
    processingTimeStart = time.perf_counter()
    vals = output.stdout
    vals = vals.decode("utf-8")
    vals = vals.split('<-->')
    processingTimeEnd = time.perf_counter()
    processingTimeDif = processingTimeEnd - processingTimeStart
    print("Processing the output from the NIOS II terminal : ", processingTimeDif, " seconds")

        #   Output capturing
    # vals[1].strip() indicates the first output from the NIOS II terminal and is stored in x
    x = vals[1].strip()

        #   Output processing
    # if x is the letter 'e', KEY0 / the top button is being pushed therefore telling the 
    # player's tank to shoot it's bullets
    if x == "e"  :
    #    print("shooting")
        return x
    # if x is the letter 'r', KEY1 / the bottom button is bieng pushed therefore telling the
    # player's tank to drop it's bomb
    elif x == "r" :
    #    print("bombing")
        return x
    else :
        # if the first character is neither of these, we have received an x-coordinate value
        # and we know that the output value in the 3rd index is the y-axis value.
        y = vals[3].strip()
        # send the received information to the process_directions function
        return process_directions(int(x), int(y))

def main():
    server_connect_start = time.perf_counter()
        # Testing NIOS II to Ecplise by just printing to the terminal
    # cmd - variable we send to eclipse
    # msg - variable we receive from eclipse

    #           --- Establishing a connection with the server ---
    # localhost in IPv4 interface
    HOST = '52.56.73.213'
    # int with port number from 1-65535
    PORT = 6969

    # arguments passed to socket() specify the address family and socket type
    # AF_INET is the Internet address family for IPv4.
    # SOCK_STREAM is the socket type for TCP (protocol that will be used)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # establish connection with the server
    s.connect((HOST, PORT))
    server_connect_end = time.perf_counter()
    server_connect_dif = server_connect_end - server_connect_start
    print("Total send_on_jtag time: ", server_connect_dif, "seconds")

    # The connection with the server must be initialised by receiving information
    # then sending (the same or different) information back
    
    # Receiving the initial word/information
    initial_cmd = s.recv(128)
    print(initial_cmd.decode("utf-8"))

    # Sending the response word/information
    word = "Player"
    s.send(bytes(word,"utf-8"))

    # Avoids errors from sending and receiving information to the server at
    # the same time
    second_cmd = s.recv(128)
    print(second_cmd.decode("utf-8"))
    s.setblocking(0)

    #           --- Connecting the stream of information from the server to NIOS II ---
    # This loop reads the received character from the server and uses the send_on_jtag()
    # function to transmit it to the NIOS II processor

    #       --- Variables and their uses ---
    #   cmd - character we will be sending to the NIOS II processor
    # Initialise the character cmd with the letter 's'
    cmd = 's'
    #   msg - character being received from the NIOS II processor
    # This variable is initialised with the first return value of send_ont_jtag(cmd)

    while True:
        # Grab the output character from the NIOS II terminal
        sendonjtag_start = time.perf_counter()
        msg = send_on_jtag(cmd)
        sendonjtag_end = time.perf_counter()
        sendonjtag_dif = sendonjtag_end - sendonjtag_start
        print("Total send_on_jtag time: ", sendonjtag_dif, " seconds")

        cmd = 's'
        # Send the received character to the server
        send_server_start = time.perf_counter()
        s.send(bytes(msg,"utf-8"))
        send_server_end = time.perf_counter()
        send_server_dif = send_server_end - send_server_start
        print("Time taken to send a char to the server : ", send_server_dif, " seconds")
        try:    # try to receive a character from the stream
            receive_server_start = time.perf_counter()
            cmd = s.recv(128)
            cmd = cmd.decode()
            receive_server_end = time.perf_counter()
            receive_server_dif = receive_server_end - receive_server_start
            print("Time taken to receive a char from the server : ", receive_server_dif, " seconds")
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
