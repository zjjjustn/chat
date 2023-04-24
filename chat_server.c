#include<chat_server.h>

int chat_socket()
{
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd = -1)
    {
        perror("Socket Error");
        return -1;
    }
    return sockfd;

}

int chat_bind(int sockfd,const int port,const char * ip)
{
    if(port <= 0 || ip == NULL || sockfd <= 0)
    {
        return -1;
    }

    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port);
    server_sockaddr.sin_addr.s_addr = inet_addr(ip);

   

    int opt = 1;
//端口复用
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    if(bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr)) == -1)
    {
        perror("bind Error");
        return -1;
    }

    listen(sockfd,36);

    return sockfd;
}

int chat_accept(int sockfd,int *client_port,char * client_ip)
{
    struct sockaddr_in client_sockaddr;
    int length = sizeof(client_sockaddr);

    int conn = accept(sockfd,(struct sockaddr*)&client_sockaddr,&length);

    if(-1 == conn)
    {
        perror("accept errror");
        return -1;
    }
    *client_port = ntohs(client_sockaddr.sin_port);
    memcpy(client_ip,inet_ntoa(client_sockaddr.sin_addr),15);


    return conn;
}


// #define SERVPORT 8080

// typedef struct online_client
// {
//     int connfd;

//     struct online_client * next;
// }Online;

// struct thread_node
// {
//     int connfd;
//     Online * head;
// };

// struct msg_node
// {
//     char chart_mode[5];
//     int connfd;
//     char msg[100];
// };

// void create_node(Online ** new_node)
// {
//     *new_node = (Online *)malloc(sizeof(Online));
// }

// void create_link(Online ** head)
// {
//     create_node(head);
//     (*head)->next = NULL;
// }

// void insert_node(Online *head,Online *new_node)
// {
//     new_node->next = head->next;
//     head->next = new_node;
// }

// void release_link(Online **head)
// {
//     Online *p = NULL;
//     p=*head;
//     while(p!=NULL)
//     {
//         *head = (*head)->next;
//         free(p);
//         p = *head;
//     }
// }

// void delete_node(struct thread_node * connfd_node)
// {
//     Online * head = NULL;
//     Online * p = NULL;
//     Online * q = NULL;
//     int connfd;

//     head = connfd_node->head;
//     connfd = connfd_node->connfd;

//     p = head->next;
//     q = head;
//     while(p!= NULL && p->connfd != connfd)
//     {
//         q = p;
//         p = p->next;
//     }
//     if(p != NULL)
//     {
//         q->next = p->next;
//         free(p);

//     }
// }
// void visit_link_one(struct thread_node *connfd_node,struct msg_node * msg_one)
// {
//     int n;
//     Online *p = NULL;

//     p = connfd_node->head->next;

//     n = strlen(msg_one->msg);
//     while(p!=NULL && p->connfd != msg_one->connfd)
//     {
//         p = p->next;
//     }
//     if(NULL == p)
//     {
//         printf("clinet is not online!\n");
//     }
//     else
//     {
//         send(p->connfd,msg_one->msg,n,0);
//     }
// }

// void visit_link_all(Online *head,char *msg)
// {
//     Online *p = NULL;
//     int n;
//     n=strlen(msg);
//     p= head->next;
//     while(p!= NULL)
//     {
//         send(p->connfd,msg,n,0);
//         p = p->next;
//     }
// }

// int msg_send_recv(struct thread_node * connfd_node)
// {
//     int i,n,m;
//     struct msg_node msg_text;
//     n = recv(connfd_node->connfd,&msg_text,sizeof(msg_text),0);

//     if(0==n)
//     {
//         printf("client is offline!\n");
//         close(connfd_node->connfd);
//         delete_node(connfd_node);
//         pthread_exit(NULL);
//     }
//     else
//     {
//         m = strlen(msg_text.msg);

//         for(i = 0; i < n;i++)
//         {
//             msg_text.msg[i] = toupper(msg_text.msg[i]);
//         }
//         if(strcmp(msg_text.chart_mode,"stoa") == 0)
//         {
//             visit_link_all(connfd_node->head,msg_text.msg);
//         }
//         else if(strcmp(msg_text.chart_mode,"stoo") == 0)
//         {
//             visit_link_one(connfd_node,&msg_text);
//         }
//         else
//         {
//             printf("chart mode error!\n");
//         }
//     }
// }

// void * client_chart(void * arg)
// {
//     struct thread_node connfd_node;

//     connfd_node = *((struct thread_node *)arg);

//     for(;;)
//     {
//         msg_send_recv(&connfd_node);
//     }
//     close(connfd_node.connfd);

//     return NULL;
// }

// int main()
// {
//     struct sockaddr_in servaddr,cliaddr;
//     int listenfd,connfd;
//     socklen_t clilen;
//     int ret;
//     pthread_t tid;

//     Online * head = NULL;
//     Online * new_node = NULL;

//     struct thread_node connfd_node;

//     create_link(&head);

//     connfd_node.head = head;

//     listenfd = socket(AF_INET,SOCK_STREAM,0);

//     bzero(&servaddr,sizeof(servaddr));
//     servaddr.sin_family = AF_INET;
//     servaddr.sin_addr.s_addr = htons(INADDR_ANY);
//     servaddr.sin_port = htons(SERVPORT);

//     bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    
//     listen(listenfd,1024);

//     while(1)
//     {
//         clilen = sizeof(cliaddr);
//         connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);

//         create_node(&new_node);
//         new_node->connfd = connfd;
        
//         insert_node(head,new_node);

//         connfd_node.connfd = connfd;
//         ret = pthread_create(&tid,NULL,client_chart,(void *)&connfd);

//     }
//     close(listenfd);
//     release_link(&head);
// }