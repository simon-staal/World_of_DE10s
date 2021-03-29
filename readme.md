World of DE-10s
===============

This repository contains the notes and project files for World of DE-10s, a 1v1 tank game developed as part of the 2nd year Information Processing module completed in Spring 2021. The project involves an IoT system where 2 FPGAs, which act as controllers, are connected to PCs which act as nodes which communicate with a TCP server hosted on an AWS client. This server then handles communication between the player nodes and a 3rd PC which is running the game in unity, and sends and receives the required information between these 3 nodes to run the game. Please find a brief guide to the repository below!


Contributors
------------
- Kaius Connway-Lai (kc319)
- Khayle Torres (kt1719)
- Nelson DaSilva (NDS19)
- Salman Dhaif (sdoif)
- Simon Staal (sts219)
- Yuna Valade (yv19)


[**AWS**](AWS)
--------------
This directory contains the permission key to the AWS instance used to host our TCP server, as well as the [*setup script*](AWS/run_server.sh) that can be run on a blank AWS instance (running linux) to fully automate the server setup process. To use it on your own instance, simply replace the `.pem` ssh key, ensure your instance allows ssh and TCP connections, and invoke the script using:

    ./run_server <Instance_IP>

This should install all dependencies required to run the TCP server client on your instance, as well as pulling the most recent version of our repository and compiling and running the server.


[**Local_Processing**](Local_Processing)
----------------------------------------
This directory contains all python scripts that manage the connection between the player nodes and TCP server, and c files that are used to program the FPGAs and process the data on the local PCs. This is closely linked with the [**Quartus**](#Quartus) directory, which contains the quartus project files required to set up the FPGA to run the c-code included in this directory using the Eclipse IDE. The sub-directory [*readme*](Local_Processing/readme.md) contains more information on the setup process.


<a name="Quartus"></a>[**Quartus**](Quartus)
----------------------
As mentioned above, this directory contains the quartus project files and platform designer files required for our FPGA controllers. A [*readme*](Quartus/readme.md) detailing the setup process can be found inside the directory.


[**TCP**](TCP)
--------------
This directory contains the c++ files used to create and test the TCP server, with the main [*Server.cpp*](TCP/Server.cpp) file being run in 
