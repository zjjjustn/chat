#include"register_service.h"
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<time.h>
#include<stddef.h>
#include"chat_dao.h"
#include"msg_define.h"
#include"client_list.h"
#include"up_line_user_service.h"

extern Link client_head;

void register_handle(int sockfd,const char * content)
{
    if(content == NULL)
    {
        return;
    }

    struct user_struct user_info;
    memcpy(&user_info,content,sizeof(struct user_struct));

    struct msg_header header;
    struct server_replay replay;
    memset(&header,0,sizeof(header));
    memset(&replay,0,sizeof(replay)); 

    header.control_mask = REGISTER_REPLAY;
    memcpy(header.header,"SQJY",4);
    header.content_len = sizeof(replay);

    char current[1024]= "\0";
    struct timespec time;
    clock_gettime(CLOCK_REALTIME,&time);//获取相对于1970到现在秒数
    struct tm nowTime;
    localtime_r(&time.tv_nsec,&nowTime);
    char current[1024];
    sprintf(current,"%04d%02d%02d%02d:%02d:%02d",nowTime.tm_year + 1900,nowTime.tm_mon,nowTime.tm_mday,
    nowTime.tm_hour,nowTime.tm_min,nowTime.tm_sec);

    int is_exist = user_is_exit_db(user_info);
    if(is_exist != -1)
    {
        //用户已经存在
        replay.code = ERROR;
        strcpy(replay.error_msg,"user is exist please change your user name");

    }
    else
    {
        char final_sql[1024]= "\0";
        replay.code = SUCCESS;
        char * sql = "insert into users (USER_NAME,USER_PASS,REGISTER_TIME) values ('%s','%s','%s')";
        sprintf(final_sql,user_info.user_name,user_info.pass_word,current);
        chat_exec_sql(final_sql,NULL,NULL,NULL);
    }
    

    char s_buffer[sizeof(header) + sizeof(replay)]= "\0";
    memcpy(s_buffer,&header,sizeof(header));
    memcpy(s_buffer + sizeof(header),&replay,sizeof(replay));

    if(-1 == send(sockfd,s_buffer,sizeof(header)+sizeof(replay),0))
    {
        perror("send login replay to user error!");
    }

}
//登陆
void user_login_handle(int sockfd,const char * content)
{
    
    if(connect == NULL)
    {
        return;
    }
    struct user_struct user_info;
    memcpy(&user_info,content,sizeof(struct user_struct));

    struct msg_header header;
    struct server_replay replay;
    memset(&header,0,sizeof(header));
    memset(&replay,0,sizeof(replay)); 

    header.control_mask = LOGIN_REPLAY;
    memcpy(header.header,"SQJY",4);
    header.content_len = sizeof(replay);

    int is_exit = user_is_exit_db(user_info);


    if(is_exit == -1)
    {
        replay.code = REGISTER_ERROR;
        strcpy(replay.error_msg,"please check you count!");

    }
    else{
        replay.code = REGISTER_SUCCESS;
    }
    //检验消息
    char s_buffer[sizeof(header) + sizeof(replay)]= "\0";
    memcpy(s_buffer,&header,sizeof(header));
    memcpy(s_buffer + sizeof(header),&replay,sizeof(replay));

    if(-1 == send(sockfd,s_buffer,sizeof(header)+sizeof(replay),0))
    {
        perror("send login replay to user error!");
    }

    if(is_exit != -1)//登陆成功
    {
        Link new_node;
        create_node(&new_node);
        new_node->sockfd = sockfd;
        memcpy(new_node->user_name,user_info.user_name,32);
        memcpy(new_node->pass_word,user_info.pass_word,32);
 
        insert_list_head(&client_head,new_node);
        //返回客户端目前在线用户
        send_up_line_users(-1,1);  
    }
 
}

int user_is_exit_db(struct user_struct user)
{
    char ** query_res;
    char final_sql[1024]="\0";
    char *sql = "select * from users where USER_NAME = '%s' and USER_PASS = '%s'";

    sprintf(final_sql,sql,user.user_name,user.pass_word);

    printf("user login query sql:%s\n",final_sql);

    int col;
    int row;

    chat_query_table(final_sql,query_res,&row,&col,NULL);

    if(row > 0)
    {
        chat_free_result(query_res);
        return 1;
    }

    return -1;
}
