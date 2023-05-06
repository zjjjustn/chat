#include"msg_send_service.h" 
#include"msg_define.h"
#include"client_list.h"
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>

extern Link client_head;

void send_msg_handle(int sockfd,const char * content)
{
    struct msg_define msg_struct;
    memset(&msg_struct,0,sizeof(msg_struct));
    memcpy(&msg_struct,content,sizeof(msg_struct));

    printf("client %d send %s msg:%s is send_all:%d\n",
        sockfd,msg_struct.user_name,msg_struct.msg,msg_struct.is_send_all);
    
    
    int fds[1024];
    char send_user[1024]= "\0";
    Link p = client_head;
    int fds[1024];
    int count = 0;
    int for_count = 0;
    while(p != NULL)
    {
        printf("upline client: ip:%s port :%s fd:%d\n",
        p->user_name,p->pass_word,p->sockfd);

        if(p->sockfd == sockfd)
        {
            strcpy(send_user,p->user_name);
        }

        if(msg_struct.is_send_all == 1)
        {
            fds[count] = p->sockfd;
        }
        else
        {
            if(strcmp(p->user_name,msg_struct.user_name) == 0)
            {
                printf("compare send user %s\n",p->user_name);
                fds[0] = p->sockfd;
                for_count = 1;
            }
        }

        count++;
        p = p->next;
    }
    for_count = (msg_struct.is_send_all == 1) ? count : for_count;

    for(size_t i = 0;i<for_count;i++)
    {
        int fd = fds[i];

        struct msg_define s_msg_struct;
        struct msg_header header;
        memset(&header,0,sizeof(header));
        memset(&s_msg_struct,0,sizeof(s_msg_struct));
        header.control_mask = UPLINE_USERS;
        header.content_len = sizeof(s_msg_struct);
        memcpy(header.header,"SQJY",4);

        strcpy(s_msg_struct.msg,msg_struct.msg);
        strcpy(s_msg_struct.user_name,send_user);
        s_msg_struct.is_send_all = msg_struct.is_send_all;

        char s_buffer[sizeof(s_msg_struct) + sizeof(header)] = "\0";
        memcpy(s_buffer,&header,sizeof(header));
        memcpy(s_buffer + sizeof(header),&s_msg_struct,sizeof(s_msg_struct));
        //发送消息
        int s_ret = send(fd,s_buffer,sizeof(s_msg_struct) + sizeof(header),0);
        if(s_ret == -1)
        {
            perror("send client msg error!");
        }
    }
}