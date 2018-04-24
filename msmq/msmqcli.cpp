/*
 * @Author: lqt 
 * @Date: 2018-04-24 09:53:47 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-24 11:30:02
 */
 #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include <sys/types.h>
    #include <unistd.h>
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
    void echo_cli(int msgid)
    {
        int pid;
        int n=0;
        pid=getpid();
        msgbufs msg;
        memset(&msg,0,sizeof(msg));
        *((int *)msg.mtext)=pid;
        msg.mtype=1;
        while(fgets(msg.mtext+4,MSGMAX,stdin)!=NULL)
        {
            n=msgsnd(msgid,&msg,4+strlen(msg.mtext+4),0);
            if(n==-1)
                ERR_EXIT("msgsnd");
            memset(msg.mtext+4,0,MSGMAX);
            if(msgrcv(msgid,&msg,MSGMAX,pid,0)<0)
                ERR_EXIT("msgrcv");
            fputs(msg.mtext+4,stdout);
             memset(msg.mtext+4,0,MSGMAX-4);
        }
    }
    int main()
    {
        int msgid=0;
        msgid=msgget(1234,0);
        if(msgid==-1)
            ERR_EXIT("msgget");
        echo_cli(msgid);
        return 0;
    }
