#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd=open("a.txt",O_RDWR,0666);
    if(fd==-1) perror("open"),exit(-1);
    struct flock lock;
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=20;
    lock.l_pid=-1;
    int res=fcntl(fd,F_SETLKW,&lock);
    if(res==-1) perror("fcntl"),exit(-1);
    printf("开始写入数据\n");
    write(fd,"HIJK",4);
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock);
    printf("写入数据成功\n");
    close(fd);
    return 0;
}