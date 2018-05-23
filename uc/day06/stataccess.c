#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
    if(access("access.c",R_OK)==0)
        printf("read!\n");
    if(access("access.c",W_OK)==0)
        printf("write\n");
    if(access("access.c",X_OK)==0)
        printf("excute\n");
    if(access("access.c",F_OK)==0)
        printf("file is here\n");
    struct stat st;
    stat("access.c",&st);
    printf("size=%d\n",st.st_size);
    return 0;
}