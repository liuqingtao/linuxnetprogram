#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd=open("a.pipe",O_RDONLY);
    if(fd==-1) perror("open"),exit(-1);
    for(;;){
        int x;
        int res=read(fd,&x,sizeof(x));
        if(res<=0) break;
        printf("x=%d\n",x);
    }
    close(fd);
}