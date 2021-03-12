#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>

#define PORT 8081

int arraycompare(char a[128], char b[128]);
void copyarray(char a[128], char b[128]);
void cleararray(char a[128]);


int main(int argc, char const *argv[])
{
    int server_fd, newconnection, newconnection2, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[128] = {0};
    char buffer2[128] = {0};
    char copybuffer[128] = {0};
    char emptybuffer[128] = {0};
    std::string hello = "Hello from server";
    int connections[10];

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

    if (listen(server_fd, 9) < 0)
    {
        perror("Listening Failed");
        exit(EXIT_FAILURE);
    }


    if ((newconnection = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("Accepting Connection Failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection Established with " << inet_ntoa(address.sin_addr) << std::endl << std::endl;

    if ((newconnection2 = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("Accepting Connection Failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection Established with " << inet_ntoa(address.sin_addr) << std::endl << std::endl;

    valread = read(newconnection , buffer, 128);
    std::cout << buffer << std::endl;
    send(newconnection , hello.c_str() , strlen(hello.c_str()) , 0 );
    std::cout << "Message Sent to C1" << std::endl;

    valread = read(newconnection2 , buffer2, 128);
    std::cout << buffer2 << std::endl;
    send(newconnection2 , hello.c_str() , strlen(hello.c_str()) , 0 );
    std::cout << "Message Sent to C2" << std::endl;


    while(1){

      cleararray(buffer);

      if(valread = read(newconnection , buffer, 128) <= 0){
        std::cout << "Connection 1 Dropped" << std::endl;
        break;
      }

      std::cout << buffer << std::endl;

      if(arraycompare(emptybuffer, buffer)){
        for(unsigned i = 0; i < 60; i++){
          send(newconnection2 , buffer , 128 , 0 );
        }
      }

    }

    fflush(stdin);
    return 0;
}


int arraycompare(char a[128], char b[128]){

  for(int i = 0; i < 128; i++){
    if(a[i] != b[i]){ return 1;};
  }
  return 0;
}

void copyarray(char a[128], char b[128]){

  for(int i = 0; i < 128; i++){
    a[i] = b[i];
  }
}

void cleararray(char a[128]){

    for(int i = 0; i < 128; i++){
      a[i] = '\0';
    }
}
