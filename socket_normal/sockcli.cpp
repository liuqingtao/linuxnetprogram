#ifndef _SOCKCLI_
#define _SOCKCLI_
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

int main()
{
    int sockcli;
    sockcli=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
    if(sockcli<0)
        ERR_EXIT("socket");
    int ret=0;
    
    sockaddr_in cliaddr;
    cliaddr.sin_family=AF_INET;
    cliaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    cliaddr.sin_port=htons(MYPORT);
    int socklen;
    socklen=sizeof(cliaddr);
    ret=connect(sockcli,(struct sockaddr*)&cliaddr,socklen);
    if(ret<0)
    {
        ERR_EXIT("connect");
    }

    char sendbuf[1024]={'0'};
    char readbuf[1024]={'0'};
    
    while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)
    {
        
        
        if(write(sockcli,&sendbuf,sizeof(sendbuf))<0)
        {
            ERR_EXIT("write");
            break;
        }
        

        if(read(sockcli,&readbuf,sizeof(readbuf))<0)
        {
            ERR_EXIT("read");
            break;
        }
        fputs(readbuf,stdout);
        memset(&sendbuf,0,sizeof(sendbuf));
        memset(&readbuf,0,sizeof(readbuf));
    }
}