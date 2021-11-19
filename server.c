#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1024

void write_file(int sockfd, struct sockaddr_in addr)
{

  char* filename = "output.txt";
  int n;
  char buffer[SIZE];
  socklen_t addr_size;

  // CREATE A FILE
  FILE* fp = fp = fopen(filename, "w");

  // Receive data
  while (1)
  {
    addr_size = sizeof(addr);
    n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, &addr_size);

    if (strcmp(buffer, "END") == 0)
    {
      break;
    }
 printf("[RECEIVE DATA FROM CLIENT] Data: %s", buffer);
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }

  fclose(fp);
}

int main()
{

  // DEFINE IP AND PORT
  char* ip = "192.168.56.102";
  const int port = 20;

  // VARIABLE
  int server_sockfd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[SIZE];
  int e;

  // CREATE  UDP SOCKET
  server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sockfd < 0)
  {
    perror("[ERROR] socket failed");
    exit(1);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (e < 0)
  {
    perror("[ERROR] bind failed");
    exit(1);
  }

  printf("[START] UDP File Server Start. \n");
  write_file(server_sockfd, client_addr);

  printf("[SUCCEED] Data transfer is successful.\n");
  printf("[CLOSED THE SERVER] Shutdown the server.\n");

  close(server_sockfd);

  return 0;
}
