#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    //pid_t pid=fork(); //open两次相当于新建两个文件表
    int fd=open("a.txt",O_CREAT|O_RDWR|O_TRUNC,0666);
    if(fd==-1) perror("open"),exit(-1);
    pid_t pid=fork();
    if(pid==0){
        printf("c:fd=%d\n",fd);
        write(fd,"son",3); //关闭子进程的fd
        close(fd);
        exit(0);
    }
    printf("f:fd=%d\n",fd);
    write(fd,"father",6);
    close(fd);//关闭父进程fd
    return 0;
}