#pragma once

#include<stdio.h>
#include"../chat_server.h"
#include"msg_define.h"



int chat_start_server(const int port,const char *ip);

void *chat_server_controller(void *arg);

int verify_header(struct msg_header header);

void process_client_msg(int sockfd,const char * content,unsigned short control_mask);
