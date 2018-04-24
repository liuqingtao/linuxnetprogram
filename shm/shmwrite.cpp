/*
 * @Author: lqt 
 * @Date: 2018-04-24 15:07:43 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-24 16:08:23
 */

#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include<sys/shm.h>
#include<cstdio>
#include<cstdlib>
#include<string.h>
#include<fcntl.h>

typedef struct stu
{
    char name[32];
    int age;
}STU;

#define ERR_EXIT(m)\
do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc,char* argv[])
{
    int shmid;
    shmid =shmget(1234,sizeof(STU),IPC_CREAT|0666);
    if(shmid==-1)
        ERR_EXIT("shmget");
    STU *p;
    p=(STU *)shmat(shmid,NULL,0);
    if(p==(void *)-1)
        ERR_EXIT("shmat");
    strcpy(p->name,"lqt");
    p->age=33;
    shmdt(p);
    //shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
