#include"register_service.h"
#include<stdio.h>
#include<string.h>
#include"msg_define.h"
#include"client_list.h"

extern Link client_head;

void register_handle(int sockfd,const char * content)
{
    if(content == NULL)
    {
        return 0;
    }

    struct user_struct user_info;
    memcpy(&user_info,content,sizeof(struct user_struct));

    Link new_node;
    create_node(&new_node);
    new_node->sockfd = sockfd;
    memcpy(new_node->user_name,user_info.user_name,32);
    memcpy(new_node->pass_word,user_info.pass_word,32);

    insert_list_head(&client_head,new_node);
    
    struct oline_user users;
    users.count = 0;
    int count = 0;
    
    Link p = client_head;
    while(p != NULL)
    {
        //users.user_name[count] = (unsigned char *)malloc(32);
        memcpy(users.user_names[count],p->user_name,32);
        printf("client: ip: %s port: %%fd:%d\n", p->user_name,p->pass_word,p->sockfd);
        count++;
        p = p->next;
    }

    users.count = count + 1;

    int s_ret = send(sockfd,&users,sizeof(users),0);
    if(s_ret == -1 || s_ret == 0)
    {
        printf("send register oline client error\n");
    }

}
