#include<stdio.h>
#include<stdlib.h>
int main(){
    extern char** environ;
    char ** p=environ;

    while(*p){
        printf("%s\n",*p);
        p++;
        //*p++;  先算p++,然后对p取*
        //**p++;
        }
    p=environ; //恢复p的指向，回到首地址
    char value[100]={};
    while(*p){
        if((strncmp("LANG=",*p,5))==0)
            strcpy(value,*p+5);
        p++;
            //*p++;  先算p++,然后对p取*
            //**p++;
        }
        printf("value=%s\n",value);
            //练习把LANG的值存入value中，并打印 
            //strncmp()可以比较前n个字符

    return 0;

}