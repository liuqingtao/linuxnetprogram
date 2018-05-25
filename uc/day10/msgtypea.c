#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<signal.h>

struct emp{
    int id;
    char name[20];
    double sal;
};
struct msg{
    long mtype;
    struct emp em;
};
void fa(int signo){
    key_t key=ftok(".",100);
    int msgid=msgget(key,0);
    if(msgid==-1) perror("msgget"),exit(-1);
    int res=msgctl(msgid,IPC_RMID,0);
    if(res==-1) perror("msgctl"),exit(-1);
}
int main(){
    signal(SIGINT,fa);
    key_t key=ftok(".",100);
    int msgid=msgget(key,IPC_CREAT|0666);
    if(msgid==-1) perror("msgget"),exit(-1);
    struct emp em1={1,"lqt",6000.0};
    struct emp em2={2,"zhy",12000.0};
    struct msg m1={1,em1};
    struct msg m2={2,em2};
    msgsnd(msgid,&m1,sizeof(m1.em),0);
    msgsnd(msgid,&m2,sizeof(m2.em),0);
    printf("send ok\n");
    while(1);//这个进程不退出
    
}