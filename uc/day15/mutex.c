#include<stdio.h>
#include<string.h>
#include<pthread.h>
unsigned int g_cn=0;
pthread_mutex_t g_mtx=PTHREAD_MUTEX_INITIALIZER;
void* thread_proc(void* arg){
    unsigned int i;
    pthread_mutex_lock(&g_mtx);
    for(i=0;i<10000000;++i){       
        ++g_cn;     
    }
    pthread_mutex_unlock(&g_mtx);
    return NULL;
}
int main(void){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread_proc,NULL);
    pthread_create(&t2,NULL,thread_proc,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("g_cn=%u\n",g_cn);
    return 0;
}