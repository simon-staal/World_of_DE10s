// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>


#define PORT 8080
#define PORTT 8081
#define O_NONBLOCK

int arraycompare(char a[128], char b[128]);
void copyarray(char a[128], char b[128]);
void sockIt(int &sock);
int letsconnect(int sock, sockaddr_in &serv_addr, std::string serverip, int a);

int main(int argc, char const *argv[])
{
    int sock = 0, valread, errcheck;
    int sock2 = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in serv_addr2;
    char buffer[128] = {0};
    char copybuffer[128] = {0};
    std::string serverip = "52.56.73.213";
    std::string whoiam = "Player";
    if(argc == 2){
      serverip = argv[1];
    }


    std::string msg;

    sockIt(sock);


    if( (errcheck = letsconnect(sock, serv_addr, serverip, 0)) < 0 ){
      std::cout << "Connect 1 Failed" << std::endl;
      return 0;
    }


    valread = read(sock , buffer, 128);
    std::cout << buffer << std::endl;

    send(sock , whoiam.c_str() , strlen(whoiam.c_str()) , 0);
    std::cout << "ID Sent" << std::endl;

    sockIt(sock2);

/*
    if( (errcheck = letsconnect(sock2, serv_addr, serverip, 1)) < 0 ){
      std::cout << "Connect 2 Failed" << std::endl;
      return 0;
    }
*/
    while((errcheck = letsconnect(sock2, serv_addr2, serverip, 1)) < 0){

    }


    valread = read(sock2 , buffer, 128);
    std::cout << buffer << std::endl;

    send(sock2 , whoiam.c_str() , strlen(whoiam.c_str()) , 0);
    std::cout << "ID Sent" << std::endl;


    while(1){
/*
        if(kbhit()){
          msg = getchar();
          send(sock , msg.c_str() , strlen(msg.c_str()) , 0 );
          std::cout << msg << " Sent" << std::endl;
        }
*/
        std::cin >> msg;

        send(sock, msg.c_str(), strlen(msg.c_str()), 0);
        std::cout << msg << " Sent" << std::endl;

        valread = read(sock2 , buffer, 128);
        std::cout << "Received " << buffer << std::endl;

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




void sockIt(int &sock){
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
      std::cout << ("\n Socket creation error \n");
  }

  std::cout << "Socket Created" << std::endl;
}




int letsconnect(int sock, sockaddr_in &serv_addr, std::string serverip, int a){


  serv_addr.sin_family = AF_INET;
  std::cout << a << std::endl;
  if(a == 0){
    serv_addr.sin_port = htons(PORT);
  }else{
    serv_addr.sin_port = htons(PORTT);
  }

  std::cout << serv_addr.sin_port << std::endl;
  std::cout << sock << std::endl;


  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, serverip.c_str() , &serv_addr.sin_addr)<=0)
  {
      std::cout << ("\nInvalid address/ Address not supported \n");
      return -1;
  }

  std::cout << "Valid IP" <<  std::endl;

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
      std::cout << ("\nConnection Failed \n");
      return -1;
  }

  std::cout << "Connection Established with Server" << std::endl;

  return 0;
}
