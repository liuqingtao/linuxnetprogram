#ifndef _UDP_CLI_
#define _UDP_CLI_
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

void echo_cli(int sock)
{
    char sendbuf[1024]={0};
    char recvbuf[1024]={0};
    sockaddr_in myaddr;
    memset(&myaddr,0,sizeof(sockaddr));
    myaddr.sin_family=AF_INET;
    myaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    myaddr.sin_port=htons(MYPORT);
    socklen_t socklen=sizeof(myaddr);
    int ret=0;
    while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)
    {
        
        sendto(sock,sendbuf,sizeof(sendbuf),0,(struct sockaddr*)&myaddr,socklen);
        ret=recvfrom(sock,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&myaddr,&socklen);
        if(ret==-1)
        {
            if(errno==EINTR)
                continue;
            ERR_EXIT("recfrom");
        }
        fputs(recvbuf,stdout);
        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));
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
    echo_cli(listensock);
    return 0;   
    

}