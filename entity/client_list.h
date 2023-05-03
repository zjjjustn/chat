#pragma once
struct client_info
{
    char user_name[16];
    char pass_word[16];
    int sockfd;

    struct client_info *next;   
};

typedef struct client_info Node;
typedef struct client_info * Link;


int create_node(Link *newnode);

void insert_list_head(Link *head, Link newnode);

void delete_node(Link *head,int sockfd);

void display_list(Link head);

void destory(Link head);
