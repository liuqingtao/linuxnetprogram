#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#define PAI 3.14159

void* area(void* arg){
    double r=*(double*)arg;
    double* s=malloc(sizeof(double));
    *s=PAI*r*r;
    pthread_exit(s);
    //以下两行不会执行
    *s=2*PAI*r;
    return s;
}
int main(void){
    printf("r= ");
    double r;
    scanf("%lf",&r);
    pthread_t tid;
    pthread_create(&tid,NULL,area,&r);
    double* s;
    pthread_join(tid,(void**)&s);
    printf("s= %g\n",*s);
    free(s);
    return 0;
}