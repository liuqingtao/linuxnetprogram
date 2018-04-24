/*
 * @Author: lqt 
 * @Date: 2018-04-24 09:08:13 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-24 11:39:03
 */

    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include<errno.h>
    #include<cstdio>
    #include<cstdlib>
    #include<string.h>
    
    #define MSGMAX 8192
    #define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
    
    struct msgbufs {
               long mtype;       /* message type, must be > 0 */
               char mtext[MSGMAX];    /* message data */
           };

    void echo_srv(int msgid)
    {
        int n=0;
        int ret=0;
        msgbufs msg;
        memset(&msg,0,sizeof(msg));
        while(1)
        {
            n=msgrcv(msgid,&msg,MSGMAX,1,0);
            if(n==-1)
                ERR_EXIT("msgrcv");
            int pid;
            pid=*((int*)msg.mtext);
            msg.mtype=pid;
            fputs(msg.mtext+4,stdout);
            ret=msgsnd(msgid,&msg,n,0);
            if(ret==-1)
                ERR_EXIT("msgsnd"); 
        }
          
    }
    int main()
    {
        int msgid;
        msgid=msgget(1234,IPC_CREAT|0666);
        if(msgid==-1)
            ERR_EXIT("msgget");
        echo_srv(msgid);
        return 0;
    }
