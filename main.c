#include<stdio.h>

int main(int argc,char ** argv)
{
    if(argc < 3)
    {
        printf("Please input port ip to start server\n");
        return -1;
    }

    int port = atoi(argv[1]);
    const char *ip = argv[2];

    printf("Chat server start with port:%d ip %s\n",port,ip);

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
        int c_port = -1;
        char c_ip[16] = '\0';
        //等待客户端连接

        int conn = chat_accept(sockfd);
        if(conn == -1)
        {
            continue;
        }

       printf("accept client port:%d ip:%s connect\n",c_port,c_ip);
    }

}