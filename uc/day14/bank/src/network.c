#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"../inc/network.h"
//TCP服务器初始化
int init(unsigned short type){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        perror("socker");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(type);
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))==-1){
        perror("bind");
        return -1;
    }
    if(listen(sockfd,1024)==-1){
        perror("listen");
        return -1;
    }
    return sockfd;      
}
//TCP服务器终结化
void deinit(int sockfd){
    close(sockfd);
}
//TCP服务器接收交易请求
int rcvreq(int sockfd,void* req,size_t len){
    int connfd=-1;
    for(;;){
        struct sockaddr_in addrcli={};
        socklen_t addrlen=sizeof(addrcli);
        connfd=accept(sockfd,(struct sockaddr*)&addrcli,&addrlen);
        if(connfd==-1){
            continue;
        }
        printf("客户交易：%s\n",inet_ntoa(addrcli.sin_addr));
        pid_t pid=fork();
        if(pid==-1){
            perror("fork");
            close(connfd);
            continue;
        }
        if(pid==0)
            break;
        close(connfd);
    }

    ssize_t rb=recv(connfd,req,len,0);
    if(rb==-1){
        perror("recv");
        close(connfd);
        return -1;
    }
    if(rb==0){
        printf("客户机已宕机！\n");
        close(connfd);
        return -1;
    }
    return connfd;
}
//TCP服务器发送交易响应
int sndres(int connfd,const void* res,size_t len){
    if(send(connfd,res,len,0)==-1){
        perror("send");
        close(connfd);
        return -1;
    }
    close(connfd);
    return 0;
}
//TCP客户机发送交易请求
int sndreq(const char* server,unsigned short type,const void* req,size_t len){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(type);
    addr.sin_addr.s_addr=inet_addr(server);
    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))==-1){
        perror("connect");
        close(sockfd);
        return -1;
    }
    if(send(sockfd,req,len,0)==-1){
        perror("send");
        return -1;
    }
    return sockfd;
}
//TCP客户机接收交易响应
int rcvres(int sockfd,void* res,size_t len){
    ssize_t rb=recv(sockfd,res,len,0);
    if(rb==-1){
        perror("recv");
        close(sockfd);
        return -1;
    }
    if(rb==0){
        printf("服务器已宕机！\n");
        close(sockfd);
        return -1;
    }
    close(sockfd);
    return 0;
}
