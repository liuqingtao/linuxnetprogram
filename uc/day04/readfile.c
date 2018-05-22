#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    int fd=open("a.txt",O_RDONLY);
    if(fd==-1) perror("opena"),exit(-1);
    int fd1=open("b.txt",O_CREAT|O_RDWR|O_TRUNC,0666);//新建文件时有权限屏蔽
    if(fd1==-1) perror("openb"),exit(-1);
    char buf[4096]={};
    
    while(1){
        int ret=read(fd,buf,sizeof(buf));
        if(ret==-1) perror("read"),exit(-1);
        if(!ret) break;
        write(fd1,buf,sizeof(buf));
    }
    close(fd);
    close(fd1);
    
}