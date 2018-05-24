#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    printf("begin\n");
    int res=execl("/bin/ls","ls","-l",NULL);
    printf("res=%d\n",res);
    printf("end\n");
}