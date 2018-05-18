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
#define PRODUCER_COUN 2
#define BUFFSIZE 10
int g_buffer[BUFFSIZE];
unsigned short in =0;
unsigned short out=0;
unsigned short consumer_id =0;
unsigned short product_id=0;

sem_t g_sem_full;
sem_t g_sem_empty;

pthread_mutex_t g_mutex;
pthread_t g_thread[CONSUMER_COUN+PRODUCER_COUN];

void *consume(void *arg)
{
    int num=(*((int*)arg));
    int i;
    while(1)
    {
        
        printf("%d wait buffer empty\n",num);
        sem_wait(&g_sem_empty);
        pthread_mutex_lock(&g_mutex);
        for(i=0;i<BUFFSIZE;i++)
        {
            printf("%2d",i);
            if(g_buffer[i]==-1)
                printf("%s","NULL");
            else
                printf("%d",g_buffer[i]);
            if(i==out)
                printf("\t<--consume");
            printf("\n");
        }
        consumer_id=g_buffer[out];
        printf("%d begin consume product %d ",num,consumer_id);
        g_buffer[out]=-1;
        out=(out+1)%BUFFSIZE;
        printf("%d end consume product %d",num,consumer_id);
        pthread_mutex_unlock(&g_mutex);
        sem_post(&g_sem_full);
        sleep(1);
    }
    return NULL;
}
void *produce(void *arg)
{
    int num=*((int*)arg);
    int i;
    while(1)
    {
        
        printf("%d wait buffer full \n",num);
        sem_wait(&g_sem_full);
        pthread_mutex_lock(&g_mutex);
        for(i=0;i<BUFFSIZE;i++)
        {
            printf("%2d",i);
            if(g_buffer[i]==-1)
                printf("%s","NULL");
            else
                printf("%d",g_buffer[i]);
            if(i==in)
                printf("\t<--produce");
            printf("\n");
        }
        printf("%d begin produce product %d ",num,product_id);
        g_buffer[in]=product_id;
        in=(in+1)%BUFFSIZE;
        printf("%d end produce product %d",num,product_id++);
        pthread_mutex_unlock(&g_mutex);
        sem_post(&g_sem_empty);
        sleep(1);
    }
    return NULL;   
}

int main(void)
{
    int i;
    int *p=(int*)malloc(sizeof(int));
    for(i=0;i<BUFFSIZE;i++)
        g_buffer[i]=-1;
    sem_init(&g_sem_full,0,BUFFSIZE);
    sem_init(&g_sem_empty,0,0);

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
    for(i=0;i<CONSUMER_COUN+PRODUCER_COUN;i++)
        pthread_join(g_thread[i],NULL);
    sem_destroy(&g_sem_full);
    sem_destroy(&g_sem_empty);
    pthread_mutex_destroy(&g_mutex);
    free(p);
    return 0;

}