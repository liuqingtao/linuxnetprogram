/*
 * @Author: lqt 
 * @Date: 2018-04-26 10:47:43 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-26 11:10:48
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
    int shmid;
    shmid=shm_open("/xyz",O_CREAT|O_RDWR,0666);
    if(shmid==-1)
    {
        ERR_EXIT("shm_open");
    }
    printf("shm create succesfully");
    if(ftruncate(shmid,sizeof(STU))==-1)
        ERR_EXIT("ftruncate");
    struct stat shm_stat;
    if(fstat(shmid,&shm_stat)==-1)
        ERR_EXIT("fstat");
    printf("size= %ld \n mode= %o \n ",shm_stat.st_size,shm_stat.st_mode&07777);
    close(shmid);
}