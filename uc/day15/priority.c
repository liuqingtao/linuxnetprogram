#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
void* pthread_proc(void* arg){
    int i;
    for(i=0;i<200;++i){
        putchar(*(char*)arg);
        sync();
        int j;
        for(j=0;j<10000000;++j);
    }
    return NULL;
}
int main(void){
    setbuf(stdout,NULL);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr,SCHED_RR); //加上这一句会无法打出“+”
    struct sched_param schedparam;
    schedparam.sched_priority=sched_get_priority_max(SCHED_RR);
    pthread_attr_setschedparam(&attr,&schedparam);
    pthread_t quick;
    pthread_create(&quick,&attr,pthread_proc,"+");
    pthread_attr_destroy(&attr);
    pthread_t slow;
    pthread_create(&slow,NULL,pthread_proc,"-");
    pthread_join(quick,NULL);
    pthread_join(slow,NULL);
    return 0;
}