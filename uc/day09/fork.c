#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void fa(int singno){
    printf("catch singno %d\n",singno);
}

int main(){
    //pid_t pid=fork(); //子进程自定义
    signal(SIGINT,fa);
    if(signal(SIGQUIT,SIG_IGN)==SIG_ERR){
        perror("signal"),exit(-1);
    }
    pid_t pid =fork(); //通过继承
    if(pid==0){
        printf("pid=%d\n",getpid());
        while(1);
    }
    printf("father over\n");
    return 0;
}