#ifndef _SOCKSVR_
#define _SOCKSVR_
#endif

#include <sys/socket.h>
#include <cstdio>
#include <sys/types.h>
#include <cstdlib>
#include <netinet/in.h>
#include <netinet/tcp.h>
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
    int listensock;
    sockaddr_in peeraddr;
    socklen_t socklen = sizeof(peeraddr);
    listensock = accept(sockfd, (struct sockaddr *)&peeraddr, &socklen);
    if (listensock < 0)
        ERR_EXIT("accept");

    printf("begin read & write\n");
    char readbuf[1024]={'0'};
    char writebuf[1024]={'0'};
    while(1)
    {
       
        
        int set = 0;
        set = read(listensock, &readbuf, sizeof(readbuf));
        if (set < 0)
         ERR_EXIT("read");
        fputs(readbuf, stdout);
        if(write(listensock,readbuf,sizeof(readbuf))<0)
            ERR_EXIT("send");
         memset(&readbuf, 0, sizeof(readbuf));

        fgets(writebuf,sizeof(writebuf),stdin);
        set=write(listensock,writebuf,sizeof(writebuf));
        if(set<0)
            ERR_EXIT("send");
        memset(&writebuf, 0, sizeof(writebuf));
    }
    
    return 0;
}
