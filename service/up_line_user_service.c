#include"up_line_user_service.h"
#include<stdio.h>
#include"msg_define.h"
#include"client_list.h"

extern Link client_head;
 
int send_up_line_users(int sockfd,int is_send_all)
{
    struct oline_user users;
    users.count = 0;
    int count = 0;
    
    Link p = client_head;
    int fds[1024];
    if(is_send_all == -1)
    {
        fds[0] = sockfd;
    }

    while(p != NULL)
    {
        //users.user_name[count] = (unsigned char *)malloc(32);
        memcpy(users.user_names[count],p->user_name,32);
        printf("upline client: ip: %s port: %%fd:%d\n", p->user_name,p->pass_word,p->sockfd);     
        //fds[count] = p->sockfd;
        if(is_send_all != -1)
        {
            fds[count] = p->sockfd; 
        }
        count++;
        p = p->next;  
    }

    users.count = count + 1;

    struct msg_header header;
    header.control_mask = UPLINE_USERS;
    header.content_len = sizeof(users);
    strcpy(header.header,"SQJY");
    char s_buffer[sizeof(users) + sizeof(header)];
    memcpy(s_buffer,&header,sizeof(header));
    memcpy(s_buffer + sizeof(header), &users, sizeof(users));

    int for_count = (is_send_all == -1) ? 1 : count;
    for(size_t i = 0; i< for_count;i++)
    {
        printf("send up line user to client%d\n",fds[i]);
        int s_ret = send (fds[i],s_buffer,sizeof(users)+ sizeof(header),0);
        if(s_ret == -1 || s_ret == 0)
        {
            printf("send register online client error\n");
            return -1;
        }
    }
    // if(is_send_all == -1)
    // {
    //     int s_ret = send(sockfd,&users,sizeof(users),0);
    //     if(s_ret == -1 || s_ret == 0)
    //     {
    //         printf("send register oline client error\n");
    //         return -1;
    //     }

    // }   
    return 1;
} 