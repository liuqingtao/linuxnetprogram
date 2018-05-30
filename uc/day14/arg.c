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
void* aver(void* arg){
    double* d=(double*)arg;
    d[2]=(d[0]+d[1])/2;
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
    double d[3];
    printf("x= ");
    scanf("%lf",&d[0]);
    printf("y= ");
    scanf("%lf",&d[1]);
    pthread_create(&tid,NULL,aver,d);
    pthread_join(tid,NULL);
    printf("z= %g\n",d[2]);
    
    return 0;
}