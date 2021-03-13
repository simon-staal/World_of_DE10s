import subprocess
import time

# Function used to send information to the board.
# This function takes an input character which is passed into the
#   .c file in Eclipse.
def send_on_jtag(cmd):
    assert len(cmd)==1, "Please make the cmd a single character"

    # Input character is sent to the NIOS II terminal.
    inputCmd = 'nios2-terminal.exe <<< {}'.format(cmd);

    # Stores the output from the NIOS II terminal
    output = subprocess.run(inputCmd, shell=True, executable='/bin/bash', stdout=subprocess.PIPE)

    # Processing of output strings from NIOS II.
    vals = output.stdout
    vals = vals.decode("utf-8")
    vals = vals.split('<-->')
    print(vals[1].strip())
    # print(vals[2].strip()) # Only returning 1 line per loop

# flat : 0, 10
# W : 10, -100
# A : 100, 10
# S : 30, 200
# D : -110, 0


def main():
    cmd = 's'
    while cmd == 's':
        # print("Python while loop running")
        send_on_jtag(cmd) # continually send the command into Eclipse
        # time.sleep(3)
    # print(res)
    
if __name__ == '__main__':
    main()
