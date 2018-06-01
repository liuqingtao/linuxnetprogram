#ifndef _SOCKSVR_
#define _SOCKSVR_
#endif

#include <sys/socket.h>
#include <cstdio>
#include <sys/types.h>
#include <cstdlib>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include<poll.h>
#include <errno.h>
#include <signal.h>
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
    signal(SIGPIPE,SIG_IGN);
    printf("create socket.......\n");
    int listensock;
    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listensock < 0)
        ERR_EXIT("socket");

    
    printf("bind socket.......\n");
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(MYPORT);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int on =1;
    if(setsockopt(listensock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
        ERR_EXIT("setsockop");
 
    if (bind(listensock, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
        ERR_EXIT("bind");
    
    printf("listen socket.......\n");
    if (listen(listensock, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    printf("accept socket.......\n");
    int conn;
    struct sockaddr_in peeraddr; 

    printf("begin read & write\n");
    char readbuf[1024]={'0'};
    char writebuf[1024]={'0'};
    int i;
    struct pollfd client[2048];
    for(i=0;i<2048;i++)
    {
        client[i].fd=-1;
    }
    client[0].fd=listensock;
    client[0].events= POLLIN;
    
    int maxi=0;
    int nready=0;
    int set = 0;
    
    while(1)
    {   nready=poll(client,maxi+1,-1);
        if(nready==-1)
        {
            if(errno==EINTR)
                continue;
            ERR_EXIT("poll");
        }
        if(nready==0)
        {
            continue;
        }
        if(client[0].revents&POLLIN)
        {
            socklen_t socklen = sizeof(peeraddr);
            conn = accept(listensock, (struct sockaddr *)&peeraddr, &socklen);
            if (conn < 0)
                ERR_EXIT("accept");
            for(i=0;i<2048;i++)
            {
                if(client[i].fd<0)
                {
                    client[i].fd=conn;
                    client[i].events=POLLIN;
                    if(i>maxi)
                        maxi=i;
                    break;
                }
                    
            }
            if(i==2048)
            {
                fprintf(stderr,"too many client");
                exit(EXIT_FAILURE);
            }
            printf("IP=%s  PORT=%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
            if(--nready<=0)
                continue;
           
        }

        for(i=1;i<=maxi;i++)
        {
            conn=client[i].fd;
            if(conn==-1)
                continue;
            if(client[i].events&POLLIN)
            {
                char readbuf[1024]={'0'};
                set = read(conn, readbuf, sizeof(readbuf));
                if (set ==-1)
                    ERR_EXIT("read");
                if(set==0)
                {
                    printf("client close\n");
                    client[i].fd=-1;
                    client[i].events=-1;
                    close(conn);
                }
                fputs(readbuf, stdout); 
                if(write(conn,readbuf,sizeof(readbuf))<0)
                    ERR_EXIT("send");                    
                memset(&readbuf, 0, sizeof(readbuf));
                if(--nready<=0)
                    break;
            }
        }
      
        /*
        fgets(writebuf,sizeof(writebuf),stdin);
        set=write(listensock,writebuf,sizeof(writebuf));
        if(set<0)
            ERR_EXIT("send");
        memset(&writebuf, 0, sizeof(writebuf));
        */

    }
    
    return 0;
}
