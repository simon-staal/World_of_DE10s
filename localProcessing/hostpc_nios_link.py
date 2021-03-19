import subprocess
import time

# Function used to send information to the board.
# This function takes an input character which is passed into the
#   .c file in Eclipse.
def send_on_jtag(cmd):
    # assert len(cmd)==1, "Please make the cmd a single character"

    # Input character is sent to the NIOS II terminal.
    inputCmd = 'nios2-terminal.exe <<< {}'.format(cmd);

    # Stores the output from the NIOS II terminal
    output = subprocess.run(inputCmd, shell=True, executable='/bin/bash', stdout=subprocess.PIPE)

    # Processing of output strings from NIOS II.
    vals = output.stdout
    vals = vals.decode("utf-8")
    vals = vals.split('<-->')
    i = 1
    #while i < 500 :
    print(vals[1].strip())
    # print(vals[3].strip())

        # print(vals[2].strip())
    #    time.sleep(0.001)
    #    i+=1
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
    cmd = 's'
    while 1:
        # print("Python while loop running")
        send_on_jtag(cmd) # continually send the command into Eclipse
        #time.sleep(1)
        #print(res)
    
if __name__ == '__main__':
    main()
