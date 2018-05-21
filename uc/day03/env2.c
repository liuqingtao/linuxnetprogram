#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    extern char** environ;
    char* value=getenv("LANG");
    printf("value=%s\n",value);
    putenv("VAR=abc");
    printf("%s\n",getenv("VAR"));
    putenv("VAR=123");
    printf("%s\n",getenv("VAR"));
    setenv("VAR","456",0);
    printf("%s\n",getenv("VAR"));
    setenv("VAR","456",1);
    printf("%s\n",getenv("VAR"));
    return 0;
}