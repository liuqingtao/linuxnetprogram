#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd=open("a.txt",O_RDWR);
    if(fd==-1) perror("open"),exit(-1);
    struct flock lock;
    lock.l_type=F_RDLCK;//读锁
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=20;
    lock.l_pid=-1;
    int res=fcntl(fd,F_SETLK,&lock);//上了读锁
    if(res==-1) perror("fcntl"),exit(-1);
    printf("lock suc!");
    sleep(15);
    printf("数据已经读完，解除锁定\n");
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock);
    sleep(10);
    printf("main over\n");
    close(fd);
    return 0;
}