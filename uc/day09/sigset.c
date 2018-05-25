#include<stdio.h>
#include<signal.h>

int main(){
    sigset_t set;
    printf("size=%d\n",sizeof(set));
    printf("%u\n",set);//有警报
    sigemptyset(&set);
    printf("%u\n",set);
    sigaddset(&set,2);
    printf("%u\n",set);
    sigaddset(&set,3);
    printf("%u\n",set);
    sigaddset(&set,7);
    printf("%u\n",set);
    sigdelset(&set,3);
    printf("%u\n",set);
    if(sigismember(&set,2)==1){
        printf("signal 2  is here\n");
    }

}