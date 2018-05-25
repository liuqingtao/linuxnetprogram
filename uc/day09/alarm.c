#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void fa(int signo){
    printf("do somethine\n");
}

int main(){
    signal(SIGALRM,fa);
    alarm(3);//3秒后产生一个SIGALRM信号
    printf("mai() run\n");
    sleep(2);
    alarm(5);//会替换掉以前的闹钟2+5
    sleep(1);
    alarm(0);//取消闹钟
    while(1);
}