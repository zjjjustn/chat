#pragma once

#include"conn_client_info.h"

struct client_info
{
    char ip[16];
    int port;
    int sockfd;

    struct client_info *next;   
};

typedef struct client_info Node;
typedef struct client_info * Link;


int create_node(Link *newnode);

void insert_list_head(Link *head, Link newnode);

void delete_node(Link *head,int sockfd);

void display_list(Link head);

int find_client(int sockfd);
