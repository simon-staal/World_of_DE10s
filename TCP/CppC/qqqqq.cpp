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
#define PORTT 8081
#define O_NONBLOCK



int arraycompare(char a[128], char b[128]);
void copyarray(char a[128], char b[128]);
void cleararray(char a[128]);
void initialiseserver(int &server_fd, sockaddr_in &address, int a);
std::pair<std::string,int> acceptnewcon(int server_fd, std::pair<std::string,int> newcon, sockaddr_in &address);
void greet(std::pair<std::string,int> &con);
int checkconnections(std::vector<std::pair<std::string, int>> connections, int &u, int &p1, int &p2);


int main(int argc, char const *argv[])
{
    int server_fd, valread, unityIN, player1IN, player2IN, errcheck, server_fd2, player1OUT, player2OUT, unityOUT;
    struct sockaddr_in address;
    struct sockaddr_in address2;

    int addrlen = sizeof(address);
    int addrlen2 = sizeof(address2);
    char p1IN[128] = {0};
    char p2IN[128] = {0};
    char uIN[128] = {0};
    char copybuffer[128] = {0};
    char emptybuffer[128] = {0};
    std::vector<std::pair<std::string, int>> connections, connections2;
    std::string msg;

    std::pair<std::string, int> defaultcon;

    initialiseserver(server_fd, address, 0);

    initialiseserver(server_fd2, address2, 1);


    for(int i = 0; i < 2; i++){
      connections.push_back(acceptnewcon(server_fd, defaultcon, address));
    }

    for(int i = 0; i < 2; i++){
      connections2.push_back(acceptnewcon(server_fd2, defaultcon, address2));
    }



    while(1){


        valread = read(connections[0].second, p1IN, 128);
        std::cout << "Read p1 " << p1IN << std::endl;
        valread = read(connections[1].second, p2IN, 128);
        std::cout << "Read p2 " << p2IN << std::endl;
        send(connections2[1].second, p1IN, 128, 0);
        send(connections2[0].second, p2IN, 128, 0);


/*
      valread = read(connections[1].second , p1IN, 128);
      std::cout << "Read from Player1 " << p1IN << std::endl;
      msg = p1IN;
      write(unityIN , msg.c_str() , strlen(msg.c_str())  );
      std::cout << "Sent to Unity" << std::endl;

      valread = read(player2IN , p2IN, 128);
      std::cout << "Read from Player2 " << p2IN << std::endl;
      msg = p2IN;
      write(unityIN , msg.c_str() , strlen(msg.c_str())  );
      std::cout << "Sent to Unity" << std::endl;
*/
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



void initialiseserver(int &server_fd, sockaddr_in &address, int a){
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
   if(a == 0){
     address.sin_port = htons( PORT );
   }else{
     address.sin_port = htons( PORTT );

   }


  // Forcefully attaching socket to the port 8080
  if ( bind(server_fd, (struct sockaddr *)&address, sizeof(address)) <0 )
  {
      perror("Binding Failed");
      exit(EXIT_FAILURE);
  }

  std::cout << "Socket Attached" << std::endl;

  return;
}



std::pair<std::string,int> acceptnewcon(int server_fd, std::pair<std::string,int> newcon, sockaddr_in &address){

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

  return newcon;
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

int checkconnections(std::vector<std::pair<std::string, int>> connections, int &u, int &p1, int &p2){

  int a = 0;
  int b = 0;

  for( int i = 0; i < connections.size(); i++){

    std::string name = connections[i].first;
    int connumber = connections[i].second;

    if(name == "Unity"){
      if(a == 0){
        std::cout << "Unity Assigned" << std::endl;
        u = connumber;
        a++;
      }else{
        std::cout << "More than 1 Unity ?????" << std::endl;
        return -1;
      }
    }else if(name == "Player"){
      if(b == 0){
        std::cout << "2 Assigned" << std::endl;
        p1 = connumber;
        b++;
      }else if(b == 1){
        std::cout << "Player2 Assigned" << std::endl;
        p2 = connumber;
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
