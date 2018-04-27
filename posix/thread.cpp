/*
 * @Author: lqt 
 * @Date: 2018-04-26 15:47:40 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-26 19:04:40
 */
#include <pthread.h>
#include <unistd.h>
#include<string.h>
#include<cstdlib>
#include<cstdio>
void *thread_routine(void *)
{
    int i;
    for(i=0;i<10;i++)
    {
        printf("B");
        fflush(stdout);
        if(i==2)
            pthread_exit((void *)"ABC");
        usleep(20);
    }
    return 0;
}
int main()
{
    pthread_t tid;
    int ret;
    if(ret=pthread_create(&tid,NULL,thread_routine,NULL)==-1)
    {
        fprintf(stderr,"pthread_create %s\n",strerror(ret));
        exit(EXIT_FAILURE);
    }
    int i;
    for(i=0;i<10;i++)
    {
        printf("A");
        fflush(stdout);
        usleep(20);
    }
    void *rval;
    if((ret=pthread_join(tid,&rval))!=0)
    {
        fprintf(stderr,"pthread_join %s\n",strerror(ret));
        exit(EXIT_FAILURE);  
    }
    printf("\npthread return:%s\n",(char *)rval);
    return 0;
}