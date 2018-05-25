#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd=open("a.pipe",O_WRONLY);//管道不要用读写
    if(fd==-1) perror("open"),exit(-1);
    int i;
    for(i=0;i<100;i++){
        write(fd,&i,sizeof(i));
        usleep(50000);
    }
    close(fd);
}