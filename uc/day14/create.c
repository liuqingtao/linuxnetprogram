#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
void myperror(const char* title,int error){
    fprintf(stderr,"%s:%s\n",title,strerror(error));
}
void* thread_proc(void* arg){
    printf("%lu线程：%s\n",pthread_self(),(char*)arg);
    return NULL;
}
int main(void){
    pthread_t tid;
    int error =pthread_create(&tid,NULL,thread_proc,"我是子线程！");
    if(error){
        myperror("pthread_create",error);
        return -1;
    }
    printf("%lu线程：我是主线程，创建了一个%lu子线程",pthread_self(),tid);
    sleep(1);
    return 0;     
}