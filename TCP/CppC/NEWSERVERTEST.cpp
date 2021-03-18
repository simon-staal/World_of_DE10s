#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <utility>
#include <vector>

#define PORT 8080

int arraycompare(char a[128], char b[128]);
void copyarray(char a[128], char b[128]);
void cleararray(char a[128]);
void initialiseserver(int &server_fd, sockaddr_in &address);
void acceptnewcon(int server_fd, std::pair<std::string,int> &newcon, sockaddr_in &address);
void greet(std::pair<std::string,int> &con);
int checkconnections(std::vector<std::pair<std::string, int>> connections, int &U, int &P1, int &P2);


int main(int argc, char const *argv[])
{
    int server_fd, valread, Unity, Player1, Player2, errcheck;
    struct sockaddr_in address;

    int addrlen = sizeof(address);
    char P1IN[128] = {0};
    char P2IN[128] = {0};
    char UIN[128] = {0};
    char copybuffer[128] = {0};
    char emptybuffer[128] = {0};
    std::vector<std::pair<std::string, int>> connections;

    std::pair<std::string, int> defaultcon;

    connections.push_back(defaultcon);
    connections.push_back(defaultcon);
    connections.push_back(defaultcon);

    initialiseserver(server_fd, address);

    acceptnewcon(server_fd, connections[0], address);
    acceptnewcon(server_fd, connections[1], address);
    acceptnewcon(server_fd, connections[2], address);

    if( ( errcheck = checkconnections(connections, Unity, Player1, Player2)) < 0){
      std::cout << ":(" << std::endl;
    }else{
      std::cout << "Connections Configured. It's going alright!" << std::endl;
    }

    std::cout << "Player1 " << Player1 << std::endl << "Player2 " << Player2 << std::endl << "Unity " << Unity << std::endl;

    while(1){

      valread = read(Player1 , P1IN, 128);
      std::cout << "Read from Player1" << std::endl;
      valread = read(Player2 , P2IN, 128);
      std::cout << "Read from Player2" << std::endl;


    }

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

  return;
}

void cleararray(char a[128]){

  for(int i = 0; i < 128; i++){
    a[i] = '\0';
  }

  return;
}



void initialiseserver(int &server_fd, sockaddr_in &address){
  int opt = 1;
  int addrlen = sizeof(address);

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
  if ( bind(server_fd, (struct sockaddr *)&address, sizeof(address)) <0 )
  {
      perror("Binding Failed");
      exit(EXIT_FAILURE);
  }

  std::cout << "Socket Attached" << std::endl;

  return;
}



void acceptnewcon(int server_fd, std::pair<std::string,int> &newcon, sockaddr_in &address){

  int addrlen = sizeof(address);

  std::cout << "Listening" << std::endl;

  if (listen(server_fd, 9) < 0)
  {
      perror("Listening Failed");
      exit(EXIT_FAILURE);
  }


  if ((newcon.second = accept(server_fd, (struct sockaddr *)&address,
                     (socklen_t*)&addrlen))<0)
  {
      perror("Accepting Connection Failed");
      exit(EXIT_FAILURE);
  }



  std::cout << "Connection Established with " << inet_ntoa(address.sin_addr) << std::endl << std::endl;

  greet(newcon);

  return;
}

void greet(std::pair<std::string,int> &con){

  std::string hello = "Hi this is the server. Who am I connected to?";
  char buffer[128] = {0};
  int valread;
  send(con.second , hello.c_str() , strlen(hello.c_str()) , 0 );
  std::cout << "Hello Sent," << std::endl;
  valread = read(con.second , buffer, 128);
  std::cout << "We are connected to "<< buffer << std::endl;
  con.first = buffer;
  return;
}

int checkconnections(std::vector<std::pair<std::string, int>> connections, int &U, int &P1, int &P2){

  int a = 0;
  int b = 0;

  for( int i = 0; i < connections.size(); i++){

    std::string name = connections[i].first;
    int connumber = connections[i].second;

    if(name == "Unity"){
      if(a == 0){
        std::cout << "Unity Assigned" << std::endl;
        U = connumber;
        a++;
      }else{
        std::cout << "More than 1 Unity ?????" << std::endl;
        return -1;
      }
    }else if(name == "Player"){
      if(b == 0){
        std::cout << "Player1 Assigned" << std::endl;
        P1 = connumber;
        b++;
      }else if(b == 1){
        std::cout << "Player2 Assigned" << std::endl;
        P2 = connumber;
        b++;
      }else{
        std::cout << "Too many playas on this server" << std::endl;
        return -1;
      }
    }
  }

  if( (a == 1) & (b == 2)){
    std::cout << "All good!" << std::endl;
    return 0;
  }else{
    std::cout << "Somethings wrong T_T" << std::endl;
    return -1;
  }
}
