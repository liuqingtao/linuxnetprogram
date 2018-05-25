#include<stdio.h>
#include<signal.h>

void fa(int signo){
    printf("catch signal %d\n",signo);
}

int main(){
    signal(SIGINT,fa);//不可能信号，处理1次
    signal(SIGQUIT,fa);
    printf("not mask\n");
    sleep(15);
    printf("begin bun to mask\n");
    sigset_t set,old;
    sigemptyset(&set);
    sigaddset(&set,2);
    sigaddset(&set,3);
    sigprocmask(SIG_SETMASK,&set,&old);
    sleep(15);
    sigset_t pend;
    sigpending(&pend); //把来过的信号放入
    if(sigismember(&pend,2)==1)
        printf("signal 2 is come\n");
    
    printf("run end,ublock mask\n");
    sigprocmask(SIG_SETMASK,&old,0);
    sleep(15);
}