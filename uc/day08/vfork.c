#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t pid=vfork();
    if(pid==0){
        printf("son run %d\n",getpid());
        sleep(2);
        printf("son over\n");
        exit(0);
    }
    printf("farther run %d\n",getpid());
}