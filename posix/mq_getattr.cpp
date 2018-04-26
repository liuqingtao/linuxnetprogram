/*
 * @Author: lqt 
 * @Date: 2018-04-25 21:13:16 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-25 22:52:30
 */
#include<unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include<errno.h>
#include<cstdio>
#include<cstdlib>

#define ERR_EXIT(m)\
do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
int main()
{
    mq_attr attr;
    int ret;
    int mqid;
    mqid=mq_open("/abc",O_RDONLY);
    ret=mq_getattr(mqid,&attr);
    if(ret==-1)
        ERR_EXIT("mq_getattr");
    printf("mq_maxmsg: %ld \n  mq_msgsize: %ld \n mq_curmsgs: %ld \n ",attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);
    return 0;     
}