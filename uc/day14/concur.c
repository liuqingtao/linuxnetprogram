#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
void* foo(void* arg){
    int i;
    for(i=0;i<100;++i){
        printf("%d",(int)arg);
        usleep((rand()%100)*1000);
    }
    return NULL;
}
int main(void){
    srand(time(NULL));
    setbuf(stdout,NULL);
    int i;
    for(i=0;i<5;++i){
        //foo((void*)i);
        pthread_t tid;
        pthread_create(&tid,NULL,foo,(void*)i);
    }
    getchar();
    return 0;
}