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
#include <sys/sem.h>
#include<cstdio>
#include<cstdlib>
#include<string.h>
#include<fcntl.h>


#define ERR_EXIT(m)\
do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
 union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};
    
int sem_create(key_t key)
{
    int semid;
    semid=semget(key,1,IPC_CREAT|IPC_EXCL|0666);
    if(semid==-1)
        ERR_EXIT("semget");
    return semid;
}
int sem_open(key_t key)
{
    int semid;
    semid=semget(key,0,0);
    if(semid==-1)
        ERR_EXIT("semget_open");
    return semid;
}
int sem_setval(int semid,int val)
{
    int ret;
    semun su;
    su.val=val;
    ret=semctl(semid,0,SETVAL,su);
    if(ret==-1)
        ERR_EXIT("setctl_setval");
    return 0;
}
int sem_getval(int semid)
{
    int ret;
    ret=semctl(semid,0,GETVAL,0);
    if(ret==-1)
        ERR_EXIT("semctl_getval");
    return ret;
}
int sem_del(int semid)
{
    int ret=0;
    ret=semctl(semid,0,IPC_RMID,NULL);
    if(ret==-1)
        ERR_EXIT("semctl_del");
    return 0;
}
int sem_p(int semid)
{
    int ret=0;
    struct sembuf sbf={0,-1,0};
    ret=semop(semid,&sbf,1);
    if(ret==-1)
        ERR_EXIT("sem_p");
    return ret;
}
int sem_v(int semid)
{
    int ret=0;
    struct sembuf sbf={0,+1,0};
    ret=semop(semid,&sbf,1);
    if(ret==-1)
        ERR_EXIT("sem_v");
    return ret;
}
int main(int argc,char* argv[])
{
    int semid;
    semid=sem_create(1234);
    semid=sem_open(1234);
    int n=sem_setval(semid,3);
    n=sem_getval(semid);
    printf("id :%d",n);
    return 0;
}
