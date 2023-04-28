#pragma once

#include<stdio.h>
#include"../chat_server.h"
#include"conn_client_info.h"


static struct conn_client_info client_info[1022];


int chat_start_server(const int port,const char *ip);
