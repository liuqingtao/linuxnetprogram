#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
    int* p1=sbrk(4);
    double* p2=sbrk(8);
    char* p3=sbrk(10);
    *p1=1;
    *p2=12.3;
    strcpy(p3,"abcd");
    printf("p1=%d\n",*p1);
    printf("p2=%lf\n",*p2);
    printf("p3=%s\n",p3);
    brk(p3),brk(p2),brk(p1);
    return 0;
}