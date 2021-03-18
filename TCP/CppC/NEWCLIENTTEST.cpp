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
void sockIt(int &sock);
int letsconnect(int sock, sockaddr_in &serv_addr, std::string serverip);

int main(int argc, char const *argv[])
{
    int sock = 0, valread, errcheck;
    struct sockaddr_in serv_addr;
    char buffer[128] = {0};
    char copybuffer[128] = {0};
    std::string serverip = "127.0.0.1";
    std::string whoiam = "Unity";
    if(argc == 2){
      serverip = argv[1];
    }

    sockIt(sock);

    if( (errcheck = letsconnect(sock, serv_addr, serverip)) < 0 ){
      std::cout << "Connect Failed" << std::endl;
      return 0;
    }

    std::string msg;

    valread = read(sock , buffer, 128);
    std::cout << buffer << std::endl;

    send(sock , whoiam.c_str() , strlen(whoiam.c_str()) , 0);
    std::cout << "ID Sent" << std::endl;

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




void sockIt(int &sock){
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
      printf("\n Socket creation error \n");
  }

  std::cout << "Socket Created" << std::endl;
}




int letsconnect(int sock, sockaddr_in &serv_addr, std::string serverip){


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

  return 0;
}
