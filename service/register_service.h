#include"msg_define.h"

void register_handle(int sockfd,const char * content);

void user_login_handle(int sockfd,const char * content);

int user_is_exit_db(struct user_struct user);