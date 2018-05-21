#include<stdio.h>
#include"add.h"
int main(){
    int r1 =add(1,2);
    double r2=add2(1.1,22.2);
    printf("%d %lf",r1,r2);
    return 0;
}