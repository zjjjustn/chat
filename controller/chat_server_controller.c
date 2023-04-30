#include"chat_server_controller.h"
#include<stdio.h>

Link client_head = NULL;

int chat_start_server(const int port,const char *ip)
{
    int sockfd = chat_socket();
    if(sockfd = -1)
    {
        return -1;
    }

    if((sockfd == chat_bind(sockfd,port,ip)) == -1)
    {
        return -1;
    }

    printf("waiting client to connect server....\n");
    
    while (1)
    {
        int c_port;
        char c_ip[16] = '\0';
        //等待客户端连接

        int conn = chat_accept(sockfd,&c_port,c_ip);
        if(conn == -1)
        {
            continue;
        }

       printf("accept client port:%d ip:%s connect\n",c_port,c_ip);
       start_detach_thread(NULL,chat_server_controller,&conn)
    }

}

void *chat_server_controller(void *arg)
{
    int sockfd = *(int*)(arg);
    int head_len = sizeof(struct msg_header);
    while(1)
    {
        char head_buf[head_len];
        int r_len = recv(sockfd,head_buf,head_len,0);
        if(r_len == 0)
        {
        }
        else if(r_len == -1)
        {

        }
    }
    pthread_exit(NULL);
}
 