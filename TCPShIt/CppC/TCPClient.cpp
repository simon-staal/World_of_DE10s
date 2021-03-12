// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

#define PORT 8080

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    std::string hello = "Hello from client";
    char buffer[1024] = {0};
    std::string serverip = "127.0.0.1";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    std::cout << "Socket Created" << std::endl;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverip.c_str() , &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    std::cout << "Valid IP" <<  std::endl;

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    std::cout << "Connection Established with Server" << std::endl << std::endl;

    std::string msg;

    while(1){

      std::cin >> msg;
      send(sock , msg.c_str() , strlen(msg.c_str()) , 0);


    }

    return 0;
}
