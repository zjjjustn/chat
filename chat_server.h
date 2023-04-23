#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<stdlib.h>
#include<ctype.h>

int chat_socket();

int chat_bind(const int port,const char *ip);