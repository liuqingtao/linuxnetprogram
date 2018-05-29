#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<limits.h>
#include<signal.h>
#include<sys/wait.h>
#include"../inc/bank.h"
//服务进程结构
typedef struct tag_Service{
    char srv_path[PATH_MAX+1]; //服务路径
    pid_t srv_pid; //服务pid
}SERVICE;
//服务进程数组
static SERVICE g_srv[]={
    {"./open",-1},
    {"./query",-1}};
//启动业务服务
void start(void){
    printf("启动业务服务....\n");
    size_t i;
    for(i=0;i<sizeof(g_srv)/sizeof(g_srv[0]);++i){
        g_srv[i].srv_pid=vfork();
        if(g_srv[i].srv_pid==-1){
            perror("vfork");
            continue;
        }
        if(g_srv[i].srv_pid==0){
            if(execl(g_srv[i].srv_path,g_srv[i].srv_path,NULL)==-1){
                perror("execl");
                _exit(EXIT_FAILURE);
            }
        }
    }
}
//停止业务服务
void stop(void){
    printf("停止业务服务.....\n");
    size_t i;
    for(i=0;i<sizeof(g_srv)/sizeof(g_srv[0]);++i){
        if(g_srv[i].srv_pid==-1){
            continue;
        }
        if(kill(g_srv[i].srv_pid,SIGINT)==-1){
            perror("kill");
        }
    }
    for(;;)
    if(wait(0)==-1){
        if(errno==ECHILD)
            break;
        perror("wait");
    }
}
int main(void){
    start();
    sleep(1);
    printf("按<回车>退出...\n");
    getchar();
    stop();
    return 0;
}

