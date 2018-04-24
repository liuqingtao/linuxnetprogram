#include<sys/socket.h>
#include<sys/types.h>
#include <unistd.h>
#include<string>
#include<errno.h>
#include<cstdlib>
#include<cstdio>

#define ERR_EXIT(m)\
do\
{\
    perror(m);\
    exit(EXIT_FAILURE);\
}while(0)

int main()
{
    int pairfd[2];
    if(socketpair(PF_UNIX,SOCK_STREAM,0,pairfd)<0)
        ERR_EXIT("socketpair");
    int var=0;
    pid_t pid;
    pid=fork();
    if(pid==-1)
        ERR_EXIT("fork");
    if(pid>0)
    {
        
        close(pairfd[1]);
        while(1)
        {
            ++var;
            printf("send data: %d\n",var);
            write(pairfd[0],&var,sizeof(var));
            read(pairfd[0],&var,sizeof(var));
            printf("revc data: %d\n",var);
            sleep(1);
        }

    }
    else if(pid==0)
    {
        close(pairfd[0]);
        while(1)
        {
        read(pairfd[1],&var,sizeof(var));
        ++var;
        write(pairfd[1],&var,sizeof(var));
        }
        
    }


    return 0;
}