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
#include <fcntl.h>


#define PORT 8080


int arraycompare(char a[128], char b[128]);
void copyarray(char a[128], char b[128]);
void cleararray(char a[128]);
void initialiseserver(int &server_fd, sockaddr_in &address);
std::pair<std::string,int> acceptnewcon(int server_fd, std::pair<std::string,int> newcon, sockaddr_in &address);
void greet(std::pair<std::string,int> &con);
int checkconnections(std::vector<std::pair<std::string, int>> connections, int &u, int &p1, int &p2);


int main(int argc, char const *argv[])
{
    int server_fd, valread, unity, player1, player2, errcheck;
    struct sockaddr_in address;

    int addrlen = sizeof(address);
    char p1IN[128] = {0};
    char p2IN[128] = {0};
    char p1OUT[128] = {0};
    char p2OUT[128] = {0};
    char uIN[128] = {0};
    char uOUT[128] = {0};
    char copybuffer[128] = {0};
    char emptybuffer[128] = {0};
    std::vector<std::pair<std::string, int>> connections;
    std::string msg;
    std::string ready = "ready";

    std::pair<std::string, int> defaultcon;

    initialiseserver(server_fd, address);


    for(int i = 0; i < 3; i++){
      connections.push_back(acceptnewcon(server_fd, defaultcon, address));
    }



    if( ( errcheck = checkconnections(connections, unity, player1, player2)) < 0){
      std::cout << ":(" << std::endl;
    }else{
      std::cout << "Connections Configured. It's going alright!" << std::endl;
    }

    std::cout << "Player1 " << player1 << std::endl << "Player2 " << player2 << std::endl << "Unity " << unity << std::endl;

    send(unity , ready.c_str() , strlen(ready.c_str()), 0 );
    send(player1 , ready.c_str() , strlen(ready.c_str()), 0 );
    send(player2 , ready.c_str() , strlen(ready.c_str()), 0 );



    std::string tmp, toP1, toP2;

    while(1){

      cleararray(p1IN);
      cleararray(p2IN);
      cleararray(uIN);

      valread = recv(player1 , p1IN, 128, MSG_DONTWAIT);
      if( strcmp(p1IN, emptybuffer) ){
        std::cout << "Read from Player1 " << p1IN << std::endl;
        tmp = p1IN;
        msg = "z" + tmp;
        send(unity , msg.c_str() , strlen(msg.c_str()), 0 );
        std::cout << "Sent to Unity" << std::endl;
      }

      valread = recv(player2 , p2IN, 128, MSG_DONTWAIT);
      if( strcmp(p2IN, emptybuffer) ){
        std::cout << "Read from Player2 " << p2IN << std::endl;
        tmp = p2IN;
        msg = "x" + tmp;
        send(unity , msg.c_str() , strlen(msg.c_str()), 0 );
        std::cout << "Sent to Unity" << std::endl;
      }

      valread = recv(unity , uIN, 128, MSG_DONTWAIT);
      if( strcmp(uIN, emptybuffer) ){
        std::cout << "Read from Unity " << uIN << std::endl;
        if(uIN[0] == 'r'){
          toP1 = uIN[0];
          toP2 = uIN[0];
          send(player1 , toP1.c_str() , strlen(toP1.c_str()), 0 );
          std::cout << "Sent to Player1" << std::endl;
          send(player2 , toP2.c_str() , strlen(toP2.c_str()), 0 );
          std::cout << "Sent to Player2" << std::endl;

        }else if(uIN[0] == 'z'){
          toP1 = uIN[1];
          send(player1 , toP1.c_str() , strlen(toP1.c_str()), 0 );
          std::cout << "Sent to Player1" << std::endl;

        }else if(uIN[0] == 'x'){
          toP2 = uIN[1];
          send(player2 , toP2.c_str() , strlen(toP2.c_str()), 0 );
          std::cout << "Sent to Player2" << std::endl;

        }

      }
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
  if ((server_fd = socket(AF_INET, SOCK_STREAM , 0)) == 0)
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

/*
  int status = fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK);


  if (status == -1){
    perror("calling fcntl");
  // handle the error.  By the way, I've never seen fcntl fail in this way
  }
*/
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
    char name2 = name.at(0);

    if(name2 == 'U'){
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
