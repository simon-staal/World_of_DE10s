Local Processing
================
This folder contains any scripts regarding the processing of data on a local PC. This includes the information received from the FPGA board and the information received from the AWS server.

Goals
-----
Local processing can be split into 2 categories, processing for the FPGA PCs (connected to the FPGA boards) and the Unity PC (which will be running the unity game).

**FPGA PC Processing**
This should be able to:
- Receive some kind of input from the FPGA board, which can then be turned into a token to be sent to the server, which will tell the Unity PC which keystroke to input.
- Receive a token from the server which it can then forward as a `char` input to the FPGA board which will cause an event to happen on the board.

**Unity PC Processing**
This should be able to:
- Listen to receive tokens from the server which will cause keystrokes to be emulated by a python script to be used as inputs to the unity game.
- Listen to receive tokens from the unity game which it can then forward to the server to be used to trigger events on the FPGA boards.

This will require scripts that can do the following:
- *FPGA PC:* Forward a token received from the server to the NIOS II Terminal
- *FPGA PC:* Process an accelerometer value from the FPGA and send it as a token to the server
- *Unity PC:* Conditionally simulate keystrokes based on input
- *Unity PC:* Capture output from unity which can be sent to the server
*N.B. Unity scripts are included in the* [**Unity**](../Unity) *directory as part of the game project files.*


=========================================================================================================================================

Setting up and establishing the Quartus environment + Handling the Eclipse & Python connection
===================================================================

Quartus File Directory
----------------------
**Main Contents:**

Project - [*Quartus/Golden_Top/DE10_LITE_GOLDEN_Top.qpf*](Quartus/Golden_Top/DE10_LITE_GOLDEN_Top.qpf)
Connections by Platform Designer/Qsys - [*Quartus/Golden_Top/nios_accelerometer.qsys*](Quartus/Golden_Top/nios_accelerometer.qsys)
Code running on the NIOS II processor - [*Local_Processing/final/hello_world_final.c*](Local_Processing/final/hello_world_final.c)
Python file - [*LocalProcessing/final/hostpc_nios_link_final.py*](LocalProcessing/final/hostpc_nios_link_final.py)

**Steps for running the NIOS II code:**

0. Generate the .sopcinfo and .elf files by running a complete compilation of the Golden_Top/DE10_LITE_GOLDEN_Top.qpf file when it is set as the top-level entity. This is done by clicking the blue play button.
1. Connect to the DE10 board by using Tools > Programmer and running the file which can be found from using Auto Detect
2. Open Eclipse through Quartus
3. Create the NIOS II project through the traditional method of right clicking the empty white space and producing a project from a template. Use the .sopcinfo file you have produced and set the template as Hello World (NOT HELLO WORLD SMALL).
4. Copy the code from localProcessing/final called hello_world_final.c and paste over the hello-world.c template file provided by Eclipse.
5. Generate the BSP by right clicking the <Project Name>_bsp folder and clicking 'NIOS II > Generate BSP'.
6. Build the project by right clicking the main <Project Name> folder and clicking 'Build Project'
7. Run the code by right clicking the same folder and clicking Run As > NIOS II process.
8. Close Eclipse (Needs to be done otherwise this causes an error when running the python file)

**Steps for connecting to the NIOS II process with python code:**

0. On a terminal, find the NIOS II terminal on your local directory. This is usually under the path: `intelFPGA_lite/<Your Quartus version>/nios2eds`, cd into this directory in the terminal of your choice; this works with the VS code terminal or powershell.
1. Run the command ./"Nios II Command Shell.bat" which causes you to enter into the NIOS II command shell; this allows you to connect with the NIOS II terminal on Eclipse through the JTAG_UART
2. Run the localProcessing/final/hostpc_nios_link_final.py file by running the command

    <Your Python type> hostpc_nios_link_final.py

3. Move your board around and inshallah it will work

**Some background on how things operate**

The connection between the file running on the NIOS II processor code and the code running on the host PC is created from the JTAG_UART we download onto the FPGA from the .qsys file. The code on the NIOS II processor opens a connection to the output stream going through the JTAG_UART using the fopen function. From this, we are able to read data coming from the python file and send data to the python file.
