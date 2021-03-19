        Quartus File Directory
    Main Contents:
Project - Golden_Top/DE10_LITE_GOLDEN_Top.qpf
Connections by Platform Designer/Qsys - Golden_Top/nios_accelerometer.qsys
Code running on the NIOS II processor - /software/tag_game/hello_world.c

    Steps for running the NIOS II code:
0. Generate the .sopcinfo and .elf files by running a complete compilation of the Golden_Top/DE10_LITE_GOLDEN_Top.qpf
    file when it is set as the top-level entity. This is done by clicking the blue play button.
1. Connect to the DE10 board by using Tools > Programmer and running the file which can be found from using 
    Auto Detect
2. Open Eclipse through Quartus
3. Create the NIOS II project through the traditional method of right clicking the empty
    white space and producing a project from a template. Use the .sopcinfo file you have produced
    and set the template as Hello World (NOT HELLO WORLD SMALL).
4. Copy the code from localProcessing called hello_world.c and paste over the hello-world.c
    template file provided by Eclipse.
5. Generate the BSP by right clicking the <Project Name>_bsp folder and clicking 'NIOS II > Generate BSP'.
6. Build the project by right clicking the main <Project Name> folder and clicking 'Build Project'
7. Run the code by right clicking the same folder and clicking Run As > NIOS II process.
8. Close Eclipse (Needs to be done otherwise this causes an error when running the python file)

    Steps for connecting to the NIOS II process with python code:
0. On a terminal, find the NIOS II terminal on your local directory. This is usually under the path:
    intelFPGA_lite/<Your Quartus version>/nios2eds
    cd into this directory in the terminal of your choice; this works with the VS code terminal or powershell.
0.5. (Sorry for the bad numbering, I forgot how to count) Run the command ./"Nios II Command Shell.bat"
    which causes you to enter into the NIOS II command shell; this allows you to connect with the NIOS II
    terminal on Eclipse through the JTAG_UART
1. Run the local/Processing/hostpc_nios_link.py file by running the command 
    <Your Python type> hostpc_nios_link.py
2. Move your board around and inshallah it will work

    Some background on how things operate
The connection between the file running on the NIOS II processor code and the code running on the host PC is 
    created from the JTAG_UART we download onto the FPGA from the .qsys file. The code on the NIOS II processor
    opens a connection to the output stream going through the JTAG_UART using the fopen function. From this, we
    are able to read data coming from the python file and send data to the python file