#include<stdio.h>
#include<signal.h>  
#include"chat_server_controller.h"

void handle_pipe(int sig)
{
     
}

int main(int argc,char ** argv)
{
    if(argc < 3)
    {
        printf("Please input port ip to start server\n");
        return -1;
    }
    handle_pipe_main();
    
    int port = atoi(argv[1]);
    const char *ip = argv[2];

    printf("Chat server start with port:%d ip %s\n",port,ip); 

    int ret = chat_start_server(port,ip);
    return ret;
}

//处理客户端pipe
void handle_pipe_main()
{
    struct sigaction sa;
    sa.sa_handler = handle_pipe;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGPIPE,&sa,NULL);
}