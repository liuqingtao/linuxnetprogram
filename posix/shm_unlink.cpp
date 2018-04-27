/*
 * @Author: lqt 
 * @Date: 2018-04-26 10:47:43 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-26 11:16:15
 */

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<cstdio>
#include<cstdlib>

#define ERR_EXIT(m)\
do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
typedef struct
{
    char name[32];
    int age;
}STU;

int main(void)
{
    
    if(shm_unlink("/xyz")==-1)
    {
        ERR_EXIT("shm_unlink");
    }
    printf("shm_unlink succefully");
    return 0;
}