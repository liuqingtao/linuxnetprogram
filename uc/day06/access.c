#include<stdio.h>
#include<unistd.h>

int main(){
    if(access("a.txt",R_OK)==0)
        printf("R_OK\n");
    if(access("a.txt",W_OK)==0)
        printf("W_OK\n");
    if(access("a.txt",X_OK)==0)
        printf("X_OK\n");
    if(access("a.txt",F_OK)==0)
        printf("F_OK\n");
    return 0;
}