/*
 * @Author: lqt 
 * @Date: 2018-04-23 21:18:28 
 * @Last Modified by:   lqt 
 * @Last Modified time: 2018-04-23 21:18:28 
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
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

#define MSGMAX 8192
int main(int argc,char *argv[])
{
    int flag =0;
    int type=0;
    char opt;
    while(1)
    {
        opt=getopt(argc,argv,"nt:");
        if(opt=='?')
            exit(EXIT_FAILURE);
        if(opt==-1)
            break;
        switch(opt)
        {
            case 'n':
                flag |=IPC_NOWAIT;
                break;
            case 't':
                type=atoi(optarg);
                break;
        }
    }
 
    int msgid;
    msgid=msgget(1234,0);
    if(msgid==-1)
        ERR_EXIT("msgget");
    msgbuf *mgptr;
    mgptr=(struct msgbuf*)malloc(sizeof(long)+MSGMAX);
    mgptr->mtype=type;
    int n=0;
    n=msgrcv(msgid,mgptr,MSGMAX,type,flag);
    if(n<0)
        ERR_EXIT("msgrcv");
    printf("read %d btypes type=%ld\n",n,mgptr->mtype);
    return 0;
}