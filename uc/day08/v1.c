#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t pid =vfork();
    if(!pid){
        printf("son :%d\n",getpid());
        execl("./b.out","b.out",NULL);
        perror("execl");
        exit(0);
    }
    waitpid(pid,0,0);
}