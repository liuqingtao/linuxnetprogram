#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void fa(int singno){
    printf("catch son %d\n",getpid());
}
int main(){
    signal(SIGINT,fa);
    if(signal(SIGQUIT,SIG_IGN)==SIG_ERR){
        perror("singla"),exit(-1);
    }
    pid_t pid=vfork();
    if(pid==0){
        printf("pid=%d\n",getpid());
        execl("./vfork2.out","vfork2.out",NULL);
        perror("execl");
        exit(-1);
    }
  
    printf("fahter over\n");
    return 0;
}