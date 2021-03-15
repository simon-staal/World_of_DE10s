// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

#define PORT 8080

int arraycompare(char a[128], char b[128]);
void copyarray(char a[128], char b[128]);

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    std::string hello = "Hello from client";
    char buffer[128] = {0};
    char copybuffer[128] = {0};
    std::string serverip = "3.19.63.165";
    if(argc == 2){
      serverip = argv[1];
    }

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

    std::cout << "Connection Established with Server" << std::endl;

    std::string msg;

    send(sock , hello.c_str() , strlen(hello.c_str()) , 0);
    std::cout << "Message Sent" << std::endl;

    valread = read(sock , buffer, 128);
    std::cout << buffer << std::endl;

    while(1){

      std::cin >> msg;
      send(sock , msg.c_str() , strlen(msg.c_str()) , 0);



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
