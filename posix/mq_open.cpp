/*
 * @Author: lqt 
 * @Date: 2018-04-25 21:13:16 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-25 22:28:48
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
    mqd_t mqid;
    mqid=mq_open("/abc",O_CREAT|O_RDWR,0666,NULL);
    if(mqid==(mqd_t)-1)
        ERR_EXIT("mq_open");
    mq_close(mqid);
    return 0;     
}