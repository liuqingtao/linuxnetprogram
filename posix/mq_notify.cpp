/*
 * @Author: lqt 
 * @Date: 2018-04-25 21:13:16 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-26 09:54:37
 */
#include<unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>
#include<errno.h>
#include<cstdio>
#include<cstdlib>
#include<string.h>

#define ERR_EXIT(m)\
do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
size_t size;
mqd_t mqid;
struct sigevent sigev;
typedef struct
{
    char name[23];
    int age;
}STU;
void handle_sigusr1(int sig)
{
    mq_notify(mqid,&sigev);
    STU stu;
    unsigned prio;
    if(mq_receive(mqid,(char *)&stu,size,&prio)==-1)
        ERR_EXIT("mq_recgive");
    printf("name: %s\n age: %d \n prio:%d \n",stu.name,stu.age,prio);
}
int main(int argc,char *argv[])
{
       
    
    mqid=mq_open("/abc",O_RDONLY);
    if(mqid==(mqd_t)-1)
        ERR_EXIT("mq_open");
    signal(SIGUSR1,handle_sigusr1);
    
    sigev.sigev_notify=SIGEV_SIGNAL;
    sigev.sigev_signo=SIGUSR1;
    
      

    mq_attr attr;
    int ret=mq_getattr(mqid,&attr);
    if(ret==-1)
        ERR_EXIT("mq_getattr");
    size=attr.mq_msgsize;
    mq_notify(mqid,&sigev);
    for(;;)
        pause();
    mq_close(mqid);
    return 0;     
}