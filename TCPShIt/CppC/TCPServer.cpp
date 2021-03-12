#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>

#define PORT 8080

int arraycompare(char* a, char* b);

int main(int argc, char const *argv[])
{
    int server_fd, newconnection, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[256] = {0};
    char buffer2[256] = {0};
    std::string hello = "Hello from server";

    std::cout << "Initialising" << std::endl;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket Creation Failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("Binding Failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket Attached" << std::endl;

    std::cout << "Listening" << std::endl;

    if (listen(server_fd, 3) < 0)
    {
        perror("Listening Failed");
        exit(EXIT_FAILURE);
    }



    if ((newconnection = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("Accepting Failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection Established with " << inet_ntoa(address.sin_addr) << std::endl << std::endl;

    send(newconnection , hello.c_str() , strlen(hello.c_str()) , 0 );
    valread = read( newconnection , buffer, 256);
    std::cout << buffer << std::endl;

    while(1){

      

    }


    return 0;
}


int arraycompare(char a[256], char b[256]){

  for(int i = 0; i < 256; i++){
    if(a[i] != b[i]){ return 0};
  }
  return 1;
}
