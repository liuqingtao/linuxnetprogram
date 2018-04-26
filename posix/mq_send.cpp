/*
 * @Author: lqt 
 * @Date: 2018-04-25 21:13:16 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-26 08:55:18
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
    if(argc!=2)
    {
        fprintf(stderr,"usage:%s <prio>",argv[0]);
        ERR_EXIT("argc");
    }
    
    mqd_t mqid;
    mqid=mq_open("/abc",O_RDWR,0666,NULL);
    if(mqid==(mqd_t)-1)
        ERR_EXIT("mq_open");
    STU stu;
    strcpy(stu.name,"lqt");
    stu.age=32;
    unsigned prio =atoi(argv[1]);
    mq_send(mqid,(const char *)&stu,sizeof(stu),prio);
    mq_close(mqid);
    return 0;     
}