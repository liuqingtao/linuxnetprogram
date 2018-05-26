#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<fcntl.h>
#include "../inc/dao.h"
const char* ID_FILE="id.dat";
//生成唯一的账号
int genid(void){
    int id=1000;
    int fd=open(ID_FILE,O_RDWR|O_CREAT,0666);
    if(fd==-1) perror("open"),exit(-1);
    if(read(fd,&id,sizeof(id))==-1) perror("read"),exit(-1);
    ++id;
    if(lseek(fd,0,SEEK_SET)==-1) perror("lseek"),exit(-1);
    if(write(fd,&id,sizeof(id))==-1) perror("write"),exit(-1);
    close(fd);
    return id;
} 
//保存账号信息
int save(const ACCOUNT* acc){
    char pathname[PATH_MAX+1];
    sprintf(pathname,"%d.acc",acc->id);
    int fd=creat(pathname,0666);
    if(fd==-1) perror("create"),exit(-1);
    if(write(fd,acc,sizeof(*acc))==-1) perror("write"),exit(-1);
    close(fd);
    return 0;
}
//获取账户信息
int get(int id,ACCOUNT* acc){
    char pathname[PATH_MAX+1];
    sprintf(pathname,"%d.acc",id);
    int fd=open(pathname,O_RDONLY);
    if(fd==-1) perror("open"),exit(-1);
    if(read(fd,acc,sizeof(&acc))==-1) perror("read"),exit(-1);
    close(fd);
    return 0;
}
//更新账号信息
int update(const ACCOUNT* acc){
    char pathname[PATH_MAX+1];
    sprintf(pathname,"%d.acc",acc->id);
    int fd=open(pathname,O_WRONLY);
    if(fd==-1) perror("open"),exit(-1);
    if(write(fd,acc,sizeof(*acc))==-1) perror("write"),exit(-1);
    close(fd);
    return 0;
}
//删除账户信息
int delete(int id){
    char pathname[PATH_MAX+1];
    sprintf(pathname,"%d.acc",id);
    if(unlink(pathname)==-1) perror("unlink"),exit(-1);
    return 0;
}
