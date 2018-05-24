#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t pid=fork();//父进程返回子进程的pid，子进程返回0
    if(pid==-1) perror("fork"),exit(-1);
    if(pid==0){  //父子进程都会判断，子进程进来
        printf("i'm son :%d! father's pid=%d\n",getpid(),getppid());
    }else{ //父子进程都会判断，父进程进来
        printf("i'm father:%d! son's pid=%d\n",getpid(),pid);
    }
    return 0;
}