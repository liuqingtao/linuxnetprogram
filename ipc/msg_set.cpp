/*
 * @Author: lqt 
 * @Date: 2018-04-23 21:18:47 
 * @Last Modified by:   lqt 
 * @Last Modified time: 2018-04-23 21:18:47 
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<errno.h>
#include<cstdio>
#include<cstdlib>
#include<string>

#define ERR_EXIT(m)\
do\
{\
    perror(m);\
    exit(EXIT_FAILURE);\
}while(0)

int main()
{
    int msgid;
    msgid=msgget(1234,0666|IPC_CREAT);
    //msgid=msgget(1234,0666|IPC_CREAT|IPC_EXCL);
    //msgid=msgget(IPC_PRIVATE,0666);
    msgid=msgget(1234,0);
    if(msgid==-1)
        ERR_EXIT("msgget");
    printf("msgget successful\n");
    printf("msgid is: %d\n",msgid);
    
    int ret;
    struct msqid_ds msgbuf;
    ret=msgctl(msgid,IPC_STAT,&msgbuf);
    printf("the mode is %o\n",msgbuf.msg_perm.mode);
    if(ret==-1)
        ERR_EXIT("msgctl");
    sscanf("600","%o",(unsigned int*)&msgbuf.msg_perm.mode);
    msgctl(msgid,IPC_SET,&msgbuf);
    printf("the mode is %o",msgbuf.msg_perm.mode);
}