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
