#include<stdio.h>
#pragma pack(1)
int main(){
    struct s{
        char c1;
        int i;
        char c2;
    };
    printf("size=%d\n",sizeof(struct s));
    return 0;
}