#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

  char *ip = "127.0.0.1";
  int port = 5566;

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));	//connect the client with the server
  printf("Connected to the server.\n");

  bzero(buffer, 1024);				//stored zero just to make sure that there is no garbage value stored
  strcpy(buffer, "Hello World, This is Nikita Mahoviya on client side.");
  printf("Client: %s\n", buffer);
  send(sock, buffer, strlen(buffer), 0);		//sent this to server

//receiving msgs back from the server
  bzero(buffer, 1024);
  recv(sock, buffer, sizeof(buffer), 0);
  printf("Server: %s\n", buffer);

//disconnected
  close(sock);
  printf("Disconnected from the server.\n");

  return 0;

}
