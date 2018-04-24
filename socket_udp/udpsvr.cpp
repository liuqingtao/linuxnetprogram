#ifndef _UDP_SVR_
#define _UDP_SVR_
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
#include<arpa/inet.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

#define MYPORT 5888
void echo_svr(int sock)
{
    char recvbuf[1024]={0};
    sockaddr_in peeraddr;
    memset(&peeraddr,0,sizeof(peeraddr));
    socklen_t socklen;
    int ret=0;
    while(1)
    {
        socklen=sizeof(peeraddr);
        memset(recvbuf,0,sizeof(recvbuf));
        ret=recvfrom(sock,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&peeraddr,&socklen);
        if(ret==-1)
        {
            if(errno=EINTR)
                continue;
            ERR_EXIT("recvfrom");
        }
        if(ret==0)
            continue;
        fputs(recvbuf,stdout);
        sendto(sock,recvbuf,ret,0,(struct sockaddr*)&peeraddr,socklen);

    }
    close(sock);
}

int main()
{
    int listensock;
    listensock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(listensock<0)
    {
        ERR_EXIT("socket");
    }
    sockaddr_in myaddr;
    memset(&myaddr,0,sizeof(sockaddr));
    myaddr.sin_family=AF_INET;
    myaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    myaddr.sin_port=htons(MYPORT);
    int ret=0;
    ret=bind(listensock,(struct sockaddr*)&myaddr,sizeof(myaddr));
    if(ret<0)
        ERR_EXIT("bind");
    echo_svr(listensock);

    return 0;   
    

}