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
    
    int maxfd;
    int nready=0;
    int fd_stdin=fileno(stdin);
    fd_set rset;
    FD_ZERO(&rset);
    
    if(fd_stdin>sockcli)
        maxfd=fd_stdin;
    else
        maxfd=sockcli;

    while(1)
    {
        FD_SET(sockcli,&rset);
        FD_SET(fd_stdin,&rset);
        int ret=0;
        nready=select(maxfd+1,&rset,NULL,NULL,NULL);
        if(nready<0)
        {
            ERR_EXIT("select");
            break;
        }
        if(nready==0)
            continue;
        if(FD_ISSET(fd_stdin,&rset))
        {
            if((fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL))
            {
                if(write(sockcli,&sendbuf,sizeof(sendbuf))<0)
                {
                    ERR_EXIT("write");
                    break;
                }
            }
            else
                ERR_EXIT("fgets");
            
        }
        if(FD_ISSET(sockcli,&rset))
        {
            ret=read(sockcli,&readbuf,sizeof(readbuf));
            if(ret<0)
            {
                ERR_EXIT("read");
                break;
            }
            if(ret==0)
            {
                printf("server close\n");
                break;
            }
            fputs(readbuf,stdout);

        }
        memset(&sendbuf,0,sizeof(sendbuf));
        memset(&readbuf,0,sizeof(readbuf));          
    }
    
}