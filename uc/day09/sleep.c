#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void fa(int signo){
    printf("catch signal %d\n",signo);
}

int main(){
    signal(SIGINT,fa);
    int res=sleep(10);
    printf("res=%d\n",res);
    printf("main()");
}