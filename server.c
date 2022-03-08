#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){


//both the client and the server are on the same machine
//hence we will use the local host
//any port no > 5000 is valid because below it are already utilised
  char *ip = "127.0.0.1";
  int port = 5566;	

//defining the varibales and structures

  int server_sock, client_sock;		//variables
  struct sockaddr_in server_addr, client_addr;	//structure
  socklen_t addr_size;				//variable
  char buffer[1024];			//used for transfer of information from one pt to other
  int n;

//cretaion of a TCP server
  server_sock = socket(AF_INET, SOCK_STREAM, 0);	//SOCK_STREAM-basically the TCP protocol
  if (server_sock < 0){				//printing error msg if any error detected
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");		//if the prgm doesnt exits then this is printed


//adding information to the server
  memset(&server_addr, '\0', sizeof(server_addr));	//address of the server;filled this structure with null value
  server_addr.sin_family = AF_INET;			//AF_INET- means internet version 4
  server_addr.sin_port = port;			//for the port no that we have specified above 5566
  server_addr.sin_addr.s_addr = inet_addr(ip);	//for the IP Address that we have specified above 127.0.0.1

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));	//no we have bind the address to the port no
  if (n < 0){						//for the error msg
    perror("[-]Bind error");
    exit(1);
  }
  printf("[+]Bind to the port number: %d\n", port);	//if the prgm doesnt exits then

//The listen() function marks a connection-mode socket (for example, those of type SOCK_STREAM), specified by the socket argument s, as accepting connections, and limits the number of outstanding connections in the socket's listen queue to the value specified by the backlog argument.

  
//here the server is waiting for the client  
  listen(server_sock, 5);				//for limiting the number of connections
  printf("Listening...\n");

  while(1){						//created a while loop that runs infintely
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);	//accepted the connection from the client
    printf("[+]Client connected.\n");

//after this go to client side

//printing msg from the client side
    bzero(buffer, 1024);				//clean the buffer variable
    recv(client_sock, buffer, sizeof(buffer), 0);	//receive from client socket into the buffer variable
    printf("Client: %s\n", buffer);


    bzero(buffer, 1024);				//clean the buffer variable
    strcpy(buffer, "Hello World, This is Nikita Mahoviya on server side.");
    printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);	//signing in to the client

//for cloding the connection
//once its disconnected, it will start the loop pair again & the server wait for the client run
    close(client_sock);
    printf("[+]Client disconnected.\n\n");

  }

  return 0;
}
