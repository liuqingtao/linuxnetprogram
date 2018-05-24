#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    printf("begin");//有\n子进程不打印，没有\n 子进程复制输出缓冲区
    fork();
    printf("end\n");
    return 0;
}