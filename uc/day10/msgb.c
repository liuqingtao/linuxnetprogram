#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>

int main(){
    key_t key=ftok(".",100);
    int msgid=msgget(key,0);
    if(msgid==-1) perror("msgget"),exit(-1);
    char buf[100]={};
    int res=msgrcv(msgid,buf,sizeof(buf),0,IPC_NOWAIT);
    if(res==-1) perror("msgget"),exit(-1);
    printf("pi=%s",buf);
}