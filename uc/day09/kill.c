#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void fa(int signo){
    printf("catch signal %d\n",signo);
}
int main(){
    pid_t pid=fork();
    if(pid==0){
        signal(SIGINT,fa);//确保signal()先执行
        printf("cpid=%d\n",getpid());
        while(1);
    }
    sleep(1);
    kill(pid,SIGINT);
    printf("main over\n");
    return 0;
}