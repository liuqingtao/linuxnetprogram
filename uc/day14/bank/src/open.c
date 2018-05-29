#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<wait.h>
#include"../inc/bank.h"
#include"../inc/network.h"
#include"../inc/dao.h"
#include"../inc/common.h"
static int g_sockfd=-1;
void sigint(int signum){
    printf("开户服务：即将停止。\n");
    deinit(g_sockfd);
    exit(0);
}

int main(void){
    if(signal(SIGINT,sigint)==SIG_ERR){
        perror("signal");
        return -1;
    }
    if(signal(SIGCHLD,sigchld)==SIG_ERR){
        perror("signal");
        return -1;
    }
    g_sockfd=init(TYPE_OPEN);
    if(g_sockfd==-1){
        return -1;
    }
    printf("开户服务：启动就绪。\n");
        OPEN_REQUEST req;
        int connfd=rcvreq(g_sockfd,&req,sizeof(req));
        if(connfd==-1){
            return -1;
        }
        OPEN_RESPOND res={""};
        ACCOUNT acc;
        if((acc.id=genid())==-1){
            sprintf(res.error,"创建账号失败！");
            goto send_respond;
        }
        strcpy(acc.name,req.name);
        strcpy(acc.passwd,req.passwd);
        acc.balance=req.balance;
        if(save(&acc)==-1){
            printf(res.error,"保存账号失败！");
            goto send_respond;
        }
        res.id=acc.id;
send_respond:
        if(sndres(connfd,&res,sizeof(res))==-1){
            return -1;
        }     
    
        return 0;
}