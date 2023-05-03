#include"client_list.h"
#include<stdio.h>

int create_node(Link *newnode)
{
    (*newnode) = (Link)malloc(sizeof(Node));

    if((*newnode) == NULL)
    {
        printf("create client info node malloc error!\n");
        return -1;
    }
    return 0;
}

void insert_list_head(Link *head,Link newnode)
{
    if((*head) == NULL)
    {
        (*head) = newnode;
        newnode->next = NULL;
    }
    else
    {
        newnode->next = (*head);
        (*head) = newnode;
    }
}

void delete_node(Link *head,int sockfd)
{
    if(*head == NULL)
    {
        printf("client list is null\n");
        return -1;
    }

    Link p,q;
    p = q = (*head);
    if((*head)->sockfd == sockfd)
    {
        printf("delect head\n");
        (*head) = (*head)->next;
        free(p);
        return 0;
    }

    while (p != NULL && p->sockfd != sockfd)
    {
        q = p;
        p = p->next;
    }

    q->next = p->next;
    free(p);
    return 0; 

}

void display_list(Link head)
{
    Link p;
    if(head == NULL)
    {
        printf("链表为空:\n");
        return;
    }

    while(p != NULL)
    {
        printf("client: ip: %s port: %%fd:%d\n", p->user_name,p->pass_word,p->sockfd);
        p = p->next;
    }
}

void destory(Link head)
{
    Link p = head;
    if(head == NULL)
    {
        return;
    }

    while(p != NULL)
    {
        free(p);
        p = NULL;
        p = p->next;
    }
}
