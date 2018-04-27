/*
 * @Author: lqt 
 * @Date: 2018-04-27 09:53:23 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-27 10:49:49
 */

#include<cstdlib>
#include<cstdio>
#include<pthread.h>
#include<unistd.h>

pthread_key_t key_tsd;
pthread_once_t once_control = PTHREAD_ONCE_INIT;
typedef struct key_tsd
{
    pthread_t tid;
    char *str;
}std_t;
void destory_routine(void * arg)
{
    printf("thread is destorying\n");
    free(arg);

}

void once_rountine()
{
    pthread_key_create(&key_tsd,destory_routine);

}
void * pthread_routine(void *arg)
{   
    
    pthread_once(&once_control,once_rountine);
    std_t *value = (std_t*)malloc(sizeof(std_t));
    value->tid=pthread_self();
    value->str=(char *)arg;
    pthread_setspecific(key_tsd,value);
    printf("%s specific %p\n",(char *)arg,value);  
    pthread_getspecific(key_tsd);
    printf("tid =%ld \n value=%s \n",value->tid,value->str);
    sleep(2);
    printf("tid =%ld \n value=%s \n",value->tid,value->str);
    
}

int main(void)
{
    //pthread_key_create(&key_tsd,destory_routine);
    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1,NULL,pthread_routine,(void *)"thread1");
    pthread_create(&tid2,NULL,pthread_routine,(void *)"thread2");
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    return 0;


}