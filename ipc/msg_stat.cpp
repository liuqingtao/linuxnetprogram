/*
 * @Author: lqt 
 * @Date: 2018-04-23 21:18:14 
 * @Last Modified by:   lqt 
 * @Last Modified time: 2018-04-23 21:18:14 
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
    if(ret==-1)
        ERR_EXIT("msgctl");
    printf("the mode is %o\n",msgbuf.msg_perm.mode);
    printf("bytes is %ld\n",msgbuf.__msg_cbytes);
    printf("number is %ld\n",msgbuf.msg_qnum);
    printf("msgmnb is %ld\n",msgbuf.msg_qbytes);
}