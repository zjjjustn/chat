#pragma once

#include<stdio.h>
#include"../chat_server.h"



int chat_start_server(const int port,const char *ip);
void *chat_server_controller(void *arg)
