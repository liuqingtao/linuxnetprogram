#ifndef _SOCKSVR_
#define _SOCKSVR_
#endif

#include <sys/socket.h>
#include <cstdio>
#include <sys/types.h>
#include <cstdlib>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include<error.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)
#define MYPORT 5888
void echo_svr(int conn)
{
    char readbuf[1024]={'0'};
    int set = 0;
    while(1)
    {        
        set = read(conn, &readbuf, sizeof(readbuf));
        if (set < 0)
         ERR_EXIT("read");
        if(set==0)
        {
            printf("client close");
            break;
        }
            
        fputs(readbuf, stdout);
        if(write(conn,readbuf,sizeof(readbuf))<0)
            ERR_EXIT("send");
         memset(&readbuf, 0, sizeof(readbuf));
    }
    
}
void *pthread__routine(void *arg)
{
    pthread_detach(pthread_self());
    long conn=(long)arg;
    echo_svr(conn);
    printf("exiting thread");
    return NULL;
} 
int main()
{
    printf("create socket.......\n");
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
        ERR_EXIT("socket");

    
    printf("bind socket.......\n");
    sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(MYPORT);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int on =1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
        ERR_EXIT("setsockop");
 
    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
        ERR_EXIT("bind");
    
    printf("listen socket.......\n");
    if (listen(sockfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    printf("accept socket.......\n");
    long listensock;
    sockaddr_in peeraddr;
    socklen_t socklen = sizeof(peeraddr);
    printf("begin read & write\n");
    
    pid_t pid;
    while(1)
    {
       listensock = accept(sockfd, (struct sockaddr *)&peeraddr, &socklen);
        if (listensock < 0)
            ERR_EXIT("accept");

        pthread_t tid;
        int ret;
        if((ret=pthread_create(&tid,NULL,pthread__routine,(void *)listensock))==-1)
        {
            fprintf(stderr,"pthread_create:%s",strerror(ret));
            exit(EXIT_FAILURE);
        }
    /*
        pid=fork();
        if(pid==-1)
            ERR_EXIT("fork");
        if(pid==0)
        {
            close(sockfd);
            echo_svr(listensock);
            exit(EXIT_SUCCESS);
        }
        else
            close(listensock);
        
    */   
    }
    
    
    return 0;
}
