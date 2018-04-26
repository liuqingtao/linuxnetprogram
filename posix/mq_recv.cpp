/*
 * @Author: lqt 
 * @Date: 2018-04-25 21:13:16 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-26 09:05:48
 */
#include<unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
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
typedef struct
{
    char name[23];
    int age;
}STU;
int main(int argc,char *argv[])
{
       
    mqd_t mqid;
    mqid=mq_open("/abc",O_RDONLY);
    if(mqid==(mqd_t)-1)
        ERR_EXIT("mq_open");
    STU stu;
    unsigned prio;
    mq_attr attr;
    int ret=mq_getattr(mqid,&attr);
    if(ret==-1)
        ERR_EXIT("mq_getattr");
    if(mq_receive(mqid,(char *)&stu,attr.mq_msgsize,&prio)==-1)
        ERR_EXIT("mq_recgive");
    printf("name: %s\n age: %d \n prio:%d",stu.name,stu.age,prio);
    mq_close(mqid);
    return 0;     
}