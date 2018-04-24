/*
 * @Author: lqt 
 * @Date: 2018-04-23 21:18:59 
 * @Last Modified by:   lqt 
 * @Last Modified time: 2018-04-23 21:18:59 
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

int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        fprintf(stderr,"usage: %s <bytes> <type>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    int len=atoi(argv[1]);
    int type=atoi(argv[2]);
    int msgid;
    msgid=msgget(1234,0);
    if(msgid==-1)
        ERR_EXIT("msgget");
    msgbuf *mgptr;
    mgptr=(struct msgbuf*)malloc(sizeof(long)+len);
    mgptr->mtype=type;
    if(msgsnd(msgid,mgptr,len,0)<0)
        ERR_EXIT("msgsnd");
    return 0;
}