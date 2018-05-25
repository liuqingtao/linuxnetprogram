#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<signal.h>

void fa(int signo){
    printf("catch signal%d\n",signo);
    printf("do something\n");
}

int main(){
    signal(SIGALRM,fa);
    struct itimerval it;
    it.it_interval.tv_sec=1;//间隔秒数
    it.it_interval.tv_usec=100000;//微秒
    it.it_value.tv_sec=3;//开始秒数
    it.it_value.tv_usec=0;
    setitimer(ITIMER_REAL,&it,0);
    while(1);
}