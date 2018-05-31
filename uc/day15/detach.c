#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
void* thread_proc(void* arg){
    pthread_detach(pthread_self());
    int i;
    for(i=0;i<200;++i){
        putchar('-');
        usleep(50000);
    }
    return NULL;
}
int main(void){
    setbuf(stdout,NULL);
    pthread_t tid;
    pthread_create(&tid,NULL,thread_proc,NULL);
    //pthread_detach(tid);
    //pthread_join(tid,NULL);
    int i;
    for(i=0;i<200;++i){
        putchar('+');
        usleep(100000);
    }
    printf("\n");
    return 0;
}