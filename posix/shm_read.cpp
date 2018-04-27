/*
 * @Author: lqt 
 * @Date: 2018-04-26 10:47:43 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-26 11:45:38
 */

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
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
    char name[32];
    int age;
}STU;

int main(void)
{
    int shmid;
    shmid=shm_open("/xyz",O_RDONLY,0);
    if(shmid==-1)
    {
        ERR_EXIT("shm_open");
    }
    printf("shm open succesfully");
    
    struct stat shm_stat;
    if(fstat(shmid,&shm_stat)==-1)
        ERR_EXIT("fstat");
    
    STU *p;
    p=(STU *)mmap(NULL,shm_stat.st_size,PROT_READ,MAP_SHARED,shmid,0);
    if(p==MAP_FAILED)
    {
        ERR_EXIT("mmap");
    }
    printf("name= %s\n age=%d \n",p->name,p->age);
    close(shmid);
}