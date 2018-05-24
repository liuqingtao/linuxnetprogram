#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    pid_t pid=fork();
    if(!pid){
        printf("son %d run \n",getpid());
        sleep(2);
        printf("son %d over\n",getpid());
        exit(100);//0-255有效
    }
    int status;
    pid_t wpid=wait(&status);
    printf("fahter %d wait\n",getpid());
    printf("wpid=%d,status=%d\n",wpid,status);
    if(WIFEXITED(status)){ //判断子进程是否正常退出
        printf("son is ok  ");
        printf("exit=%d\n",WEXITSTATUS(status));
    }
}