#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd=open("a.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd==-1) perror("open"),exit(-1);
    int fd2=dup(fd);
    printf("fd=%d,fd2=%d",fd,fd2);
    int fd3=dup2(fd2,100);
    printf("fd3=%d",fd3);
    write(fd,"abc",3);//复制了描述符 没复制文件表（共用）
    write(fd2,"123",3);
    int fd4=open("b.txt",O_RDWR|O_CREAT,0666);
    if(fd4==-1) perror("openb"),exit(-1);
    int fd5=dup2(fd,fd4);
    printf("fd4=%d,fd5=%d\n",fd4,fd5);
    write(fd4,"456",3);//传入的是5
    close(fd);
    close(fd2);
    close(fd3);
}