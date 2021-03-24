import subprocess
import time

# Function used to send information to the board.
# This function takes an input character which is passed into the
#   .c file in Eclipse.
def send_on_jtag(cmd):
    # assert len(cmd)==1, "Please make the cmd a single character"

    # Input character is sent to the NIOS II terminal.
    inputTimeStart = time.perf_counter()
    inputCmd = 'nios2-terminal.exe <<< {}'.format(cmd);
    inputTimeEnd = time.perf_counter()
    inputTimeDif = inputTimeEnd - inputTimeStart
    print("Sending character to NIOS II terminal : ", inputTimeDif, " seconds")

    # Stores the output from the NIOS II terminal
    outputTimeStart = time.perf_counter()
    output = subprocess.run(inputCmd, shell=True, executable='/bin/bash', stdout=subprocess.PIPE)
    outputTimeEnd = time.perf_counter()
    outputTimeDif = outputTimeEnd - outputTimeStart
    print("Retrieving character from NIOS II terminal : ", outputTimeDif, " seconds")

    # Processing of output strings from NIOS II.
    processingTimeStart = time.perf_counter()
    vals = output.stdout
    vals = vals.decode("utf-8")
    vals = vals.split('<-->')
    processingTimeEnd = time.perf_counter()
    processingTimeDif = processingTimeEnd - processingTimeStart
    print("Processing the output from the NIOS II terminal : ", processingTimeDif, " seconds")

    i = 1
    while i < 20 :
        print(vals[i].strip())
        #time.sleep(0.001)
        i+=1

    # print("End")
        
# Decreasing time between prints along with time between fprints.
# Decrease time between fprints as we increase the number of fprints.
# Time between fprints = time spacing between points where we obtain the WASD value
# Total time of delays in c file = time taken for output file to be ready
# Maximise time between fprints, minimise total time

    # Controller orientation
# flat : 0, 10
# NM : 0, 150
# W : 0, 30
# A : 100, 10
# S : 0, 220
# D : 130, 100
# TL : 100, 0
# TR : -130, -25
# BL : 70, 200
# BR : -100, 200

    # Flat orientation
# flat : 0, 10
# W : -10, -120
# A : 100, 10
# S : 0, 100
# D : -80, 0
# TL : 60,  -80
# TR : -100, -100
# BL : 60, 120
# BR : -100, 60

def main():
    start_time = time.time()

    cmd = 's'
    start_time = time.perf_counter()
        # print("Python while loop running")
    # while 1:
    send_on_jtag(cmd) # continually send the command into Eclipse
    current_time = time.perf_counter()
    total_elapsed_time = current_time - start_time
    print("Total send_on_jtag time: ", elapsed_time, "seconds")

if __name__ == '__main__':
    main()
