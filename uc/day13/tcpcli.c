#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(int argc,char*argv[]){
    if(argc<3){
        printf("用法：%s<服务器IP>%s<服务器端口>\n",argv[0],argv[1]);
        return -1;
    }
    printf("客户机：创建网络流套接字....\n");
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        perror("socket");
        return -1;
    }
    printf("客户机：准备地址并连接....\n");
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))==-1){
        perror("connect");
        return -1;
    }
    printf("客户机：发送请求并接收响应....\n");
    for(;;){
        printf("> ");
        char buf[1024];
        gets(buf);
        if(!strcmp(buf,"!"))
            break;
        if(send(sockfd,buf,strlen(buf)+1,0)==-1){
            perror("send");
            return -1;
        }
        ssize_t rb=recv(sockfd,buf,sizeof(buf),0);
        if(rb==-1){
            perror("recv");
            return -1;
        }
        if(rb==0){
            printf("客户机：服务器已经宕机!\n");
            break;
        }
        printf("< %s\n",buf);
    }
    printf("客户机：关闭套接字....\n");
    if(close(sockfd)==-1){
        perror("close");
        return -1;
    }
    printf("客户机：完成！\n");
    return 0;
}