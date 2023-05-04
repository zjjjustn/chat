#include"register_service.h"
#include<stdio.h>
#include<string.h>
#include"msg_define.h"
#include"client_list.h"
#include"up_line_user_service.h"

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

    send_up_line_users(sockfd,-1);
    

}
