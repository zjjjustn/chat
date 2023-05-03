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
    struct msg_header header;
    while(1)
    {
        int r_len = recv(sockfd,&header,head_len,0);
        if(r_len == 0 || r_len == -1)
        {
            //客户端关闭连接
            printf("client cut connection!\n");
            break;
        }
        //解析消息头
        if(strncmp((const char*)header.header,"SQJY",4) == 0)
        {
            //符合协议处理消息
            if(verify_header(header) == -1)
            {
                continue;
            }
            //接收正文
            char content[header.content_len];
            r_len = recv(sockfd,content,header.content_len,0);
            if(r_len == 0 || r_len == -1)
            {
                printf("client cut connection!\n");
                break;
            }
            //传递下一层处理    
            process_client_msg(sockfd,content,header.control_mask);
        }
        else{
            printf("client %d send error header:%s\n",sockfd,header.header);
            break;
        }
    }
    delect_node(&client_head,sockfd);
    close(sockfd);
    pthread_exit(NULL);
}
//校验消息头
int verify_header(struct msg_header header)
{
    if(header.content_len == -1)
    {
        return -1;
    }
    if(header.control_mask == -1)
    {
        return -1;
    }
}

void process_client_msg(int sockfd,const char * content,unsigned short control_mask)
{
    switch(control_mask)
    {
        case LOGIN:
            break;
        case REGISTER:
            break;
        
        default:
            break;
    }
}
