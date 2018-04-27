/*
 * @Author: lqt 
 * @Date: 2018-04-27 14:05:13 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-27 18:08:23
 */
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include<string.h>
#include<cstdlib>
#include<cstdio>



#define CONSUMER_COUN 1
#define PRODUCER_COUN 1
pthread_mutex_t g_mutex;
pthread_cond_t g_cond;
pthread_t g_thread[CONSUMER_COUN+PRODUCER_COUN];
int nready=0;

void *consume(void *arg)
{
    int num=*((int*)arg);
    free(arg);
    while(1)
    {       
        
        pthread_mutex_lock(&g_mutex);
        while(nready==0)
        {
            printf("%d begin wait a condtion\n",num);
            pthread_cond_wait(&g_cond,&g_mutex);
        }
        printf("%d end wait condtion\n",num);
        --nready;
        pthread_mutex_unlock(&g_mutex);
        
        sleep(1);
    }
    return NULL;
}
void *produce(void *arg)
{
    int num=*((int*)arg);
    free(arg);
    while(1)
    {
        
        
        pthread_mutex_lock(&g_mutex);
        ++nready;
        pthread_cond_signal(&g_cond);
        printf("%d singal.....\n",num);
        pthread_mutex_unlock(&g_mutex);
        sleep(1);
    }
    return NULL;   
}

int main(void)
{
    int i;
    int *p=(int*)malloc(sizeof(int));
    pthread_cond_init(&g_cond,NULL);
    pthread_mutex_init(&g_mutex,NULL);
    for(i=0;i<CONSUMER_COUN;i++)
    {
        *p=i;
        pthread_create(&g_thread[i],NULL,consume,p);
    }
    for(i=0;i<PRODUCER_COUN;i++)
    {
        *p=i;
        pthread_create(&g_thread[CONSUMER_COUN+i],NULL,produce,p);
    }
    for(i=0;i<(CONSUMER_COUN+PRODUCER_COUN);i++)
        pthread_join(g_thread[i],NULL);

    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_cond);
    return 0;

}