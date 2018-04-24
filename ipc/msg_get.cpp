/*
 * @Author: lqt 
 * @Date: 2018-04-23 21:18:41 
 * @Last Modified by:   lqt 
 * @Last Modified time: 2018-04-23 21:18:41 
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
    //int msgvar;
    //msgvar=msgctl(msgid,IPC_RMID,0);
    //if(msgvar==-1)
        //ERR_EXIT("msgctl");
    //printf("msgid delete successful\n");
}