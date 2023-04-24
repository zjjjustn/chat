#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<stdlib.h>
#include<ctype.h>
#include<arpa/inet.h>

int chat_socket();

int chat_bind(int sockfd,const int port,const char *ip);

int chat_accept(int sockfd,int *client_port,char * client_ip);