#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<wait.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int g_sockfd=-1;//监听套接字
int connfd=-1;//连接套接字
void sigint(int signum){
    if(g_sockfd!=-1){
        printf("\n服务器：关闭监听套接字.....\n");
        close(g_sockfd);
        printf("服务器：完成！\n");
    }
    if(connfd!=-1){
        printf("%d子进程：关闭连接套接字.....\n",getpid());
        close(connfd);
        printf("%d子进程：完成\n",getpid());
    }
    
    exit(0);
}
void sigchld(int signum){
    for(;;){
        pid_t pid=waitpid(-1,0,WNOHANG);
        if(pid==-1){
            if(errno!=ECHILD){
                perror("waitpid");
                exit(-1);
            }
            printf("服务器：全部子进程都已退出。\n");
            break;
        }
        if(pid)
            printf("服务器：发现%d子进程退出。\n",pid);
        else {
            printf("服务器：暂时没有子进程退出。\n");
            break;
        }
            

    }
    
}
int main(int argc,char* argv[]){
    if(argc<2){
        printf("用法:%s<端口号>\n",argv[0]);
        return -1;
    }
    if(signal(SIGINT,sigint)==SIG_ERR){
        perror("signal");
        return -1;
    }
    if(signal(SIGCHLD,sigchld)==SIG_ERR){
        perror("signal");
        return -1;
    }
    printf("服务器：创建网络流套接字....\n");
    g_sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(g_sockfd==-1){
        perror("socket");
        return -1;
    }
    printf("服务器：准备地址并绑定....\n");
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[1]));
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(g_sockfd,(struct sockaddr*)&addr,sizeof(addr))==-1){
        perror("bind");
        return -1;
    }
    printf("服务器：监听套接字.....\n");
    if(listen(g_sockfd,1024)==-1){
        perror("listen");
        return -1;
    }
    for(;;){
        printf("服务器：等待连接请求.....\n");
        struct sockaddr_in addrcli={};
        socklen_t addrlen=sizeof(addrcli);
        connfd=accept(g_sockfd,(struct sockaddr*)&addrcli,&addrlen);
        if(connfd==-1){
            perror("accept");
            return -1;
        }
        printf("服务器：接受了来自 %s:%u 客户机的连接请求.创建子进程为其服务...\n",
                inet_ntoa(addrcli.sin_addr),ntohs(addrcli.sin_port));
        pid_t pid=fork();
        if(pid==-1){
            perror("fork");
            return -1;
        }
        if(pid==0){
            if(close(g_sockfd)==-1){
                perror("close");
                return -1;
            }
            g_sockfd=-1;
            for(;;){
                char buf[1024];
                printf("%d子进程：接收请求....\n",getpid());
                ssize_t rb=recv(connfd,buf,sizeof(buf),0);
                if(rb==-1){
                    perror("recv");
                    return -1;
                }
                if(rb==0){
                    printf("%d子进程：客户机已关闭连接....\n",getpid());
                    break;
                }
                printf("%d子进程：发送响应....\n",getpid());
                if(send(connfd,buf,rb,0)==-1){
                    perror("send");
                    return -1;
                }
            }
            printf("%d子进程：关闭连接套接字.....\n",getpid());
            if(close(connfd)==-1){
                perror("close");
                return -1;
            }
            printf("%d子进程：即将退出.\n",getpid());
            return 0;
        }
        if(close(connfd)==-1){
            perror("close");
            return -1;
        }
        connfd=-1;
    }
    return 0;
}