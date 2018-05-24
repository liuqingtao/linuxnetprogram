#include<signal.h>
#include<stdlib.h>

void fa(int signo){
    printf("hello\n");
}
int main(){
    int res=signal(SIGALRM,fa);
    printf("pid=%d\n",getpid());
    while(1);
}