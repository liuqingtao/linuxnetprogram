/*
 * @Author: lqt 
 * @Date: 2018-04-25 21:13:16 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-25 22:33:12
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
    mq_unlink("/abc");
    return 0;     
}