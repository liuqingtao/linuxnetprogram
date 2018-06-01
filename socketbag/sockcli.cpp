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
struct packet {
    int len;
    char buf[1024];
};
ssize_t readn(int fd,void* buf,size_t count){
    size_t nleft=count;
    ssize_t nread;
    char *bufp=(char*) buf;
    while(nleft>0){
        if((nread=read(fd,bufp,nleft))<0){
            if(errno==EINTR)
                continue;
            return -1;
        }else if(nread==0){
            return count-nleft;
        }
        bufp+=nread;
        nleft-=nread;

    }
    return count;
}
ssize_t writen(int fd,const void* buf,size_t count){
    size_t nleft=count;
    ssize_t nwritten;
    char *bufp=(char*) buf;
    while(nleft>0){
        if((nwritten=write(fd,bufp,nleft))<0){
            if(errno==EINTR)
                continue;
            return -1;
        }else if(nwritten==0){
            continue;
        }
        bufp+=nwritten;
        nleft-=nwritten;

    }
    return count;
}
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
    struct packet sendbuf;
    struct packet recvbuf;
    memset(&sendbuf,0,sizeof(sendbuf));
    memset(&recvbuf,0,sizeof(recvbuf));
    //char sendbuf[1024]={'0'};
    //char readbuf[1024]={'0'};
    
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
            if((fgets(sendbuf.buf,sizeof(sendbuf.buf),stdin)!=NULL))
            {
                int n=strlen(sendbuf.buf);
                sendbuf.len=htonl(n);
                if(writen(sockcli,&sendbuf,4+n)<0)
                {
                    ERR_EXIT("writen");
                    break;
                }
            }
            else
                ERR_EXIT("fgets");
            
        }
        if(FD_ISSET(sockcli,&rset))
        {
            struct packet recvbuf;
            memset(&recvbuf,0,sizeof(recvbuf));
            ret=readn(sockcli,&recvbuf.len,4);
             if(ret==-1)
            {
                ERR_EXIT("readn");
                break;
            }else if(ret<4)
            {
                printf("server close\n");
                break;
            }
            int n=ntohl(recvbuf.len);
            ret=readn(sockcli,recvbuf.buf,n);
            if(ret==-1)
            {
                ERR_EXIT("readn");
                break;
            }else if(ret<n)
            {
                printf("server close\n");
                break;
            }
            fputs(recvbuf.buf,stdout);

        }
        memset(&sendbuf,0,sizeof(sendbuf));
        memset(&recvbuf,0,sizeof(recvbuf));        
    }
    
}