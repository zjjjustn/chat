#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<ctype.h>

#define SERVPORT 8080

struct msg_node
{
    char chart_mode[5];
    int connfd;
    char msg[100];
};

void * read_thread(void * arg)
{
    char recvline[100];
    int sockfd;
    int n;

    sockfd = *((int *)arg);

    while(1)
    {
        n = recv(sockfd,recvline,sizeof(recvline),0);

        recvline[n]='\0';

        printf("%s\n",recvline);
    }
    return NULL;
}

void *write_thread(void *arg)
{
    char sendline[100];
    struct msg_node msg_text;
    int choice;
    int sockfd;
    sockfd = *((int*)arg);

    while(1)
    {
        printf("please choice:\n");
        printf("1.say to all\n");
        printf("2.say to one\n");

        scanf("%d",&choice);
        if(choice == 1)
        {
            strcpy(msg_text.chart_mode,"stoa");
        }
        else if(choice == 2)
        {
            strcpy(msg_text.chart_mode,"stoo");
            printf("please input friend id!\n");
            scanf("%d",&msg_text.connfd);
        }
        else
        {
            printf("input error!\n");
            continue;
        }

        scanf("%s",sendline);
        strcpy(msg_text.msg,sendline);

        send(sockfd,&msg_text,sizeof(msg_text),0);
    }

    pthread_exit(NULL);
}

int main(int argc,char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    
    pthread_t tid_read;
    pthread_t tid_write;
    int ret;

    if(argc !=2)
    {
        printf("need server IP!\n");
        exit(0);
    }

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVPORT);
    servaddr.sin_addr.s_addr= inet_addr(argv[1]);

    connect(sockfd,(struct sockaddr*) &servaddr,sizeof(servaddr));

    ret = pthread_create(&tid_read,NULL,read_thread,(void*)&sockfd);
    ret = pthread_create(&tid_read,NULL,write_thread,(void*)&sockfd);

    pthread_detach(tid_write);
    pthread_join(tid_read,NULL);

    close(sockfd);

    return 0;

    
}