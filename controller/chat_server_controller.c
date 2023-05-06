#include"chat_server_controller.h"
#include"client_list.h"
#include"msg_send_service.h" 
#include"../entity/msg_define.h"
#include"chat_dao.h"
#include"register_service.h"

#include<stdio.h>

Link client_head = NULL;

int chat_start_server(const int port,const char *ip)
{
    int ret = chat_open_db("/home/ubuntu/working/chat/chat.db");
    if(ret != 0)
    {
        return;
    }
    int sockfd = chat_socket();
    if(sockfd == -1)
    {
        return -1;
    }

    if((sockfd == chat_bind(sockfd,port,ip)) == -1)
    { 
        return -1;
    }

    printf("waiting client to connect server....\n");
    
    while(1)
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
       start_detach_thread(NULL,chat_server_controller,&conn);
    }
    
    chat_close_db();

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
    //send all upline
    send_up_line_users(-1,1);

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
        case USER_LOGIN:
            user_login_handle(sockfd,content);
            break;
        case REGISTER:
            register_handle(sockfd,content);
            break;
        case MSG_SEND:
            send_msg_handle(sockfd,content);
            break;
        
        default:
            break;
    }
}
