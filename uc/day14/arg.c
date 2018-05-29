#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<pthread.h>
#define PAI 3.14159
void* area(void* arg){
    float r=*(float*)arg;
    *(float*)arg=PAI*r*r;
    return NULL;
}
typedef struct tag_Pyth{
    double a;
    double b;
    double c;
} PYTH,*PPYTH;
void* _pyth(void* arg){
    PPYTH pyth=(PPYTH)arg;
    pyth->c=sqrt(pyth->a*pyth->a+pyth->b*pyth->b);
    return NULL;
}
int main(void){
    printf("r= ");
    float rs;
    scanf("%f",&rs);
    pthread_t tid;
    pthread_create(&tid,NULL,area,(void*)&rs);
    pthread_join(tid,NULL);
    printf("s=%g\n",rs);
    PYTH pyth;
    printf("a= ");
    scanf("%lf",&pyth.a);
    printf("b= ");
    scanf("%lf",&pyth.b);
    pthread_create(&tid,NULL,_pyth,&pyth);
    pthread_join(tid,NULL);
    printf("c=%g\n",pyth.c);
    return 0;
}