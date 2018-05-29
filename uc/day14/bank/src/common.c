#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<wait.h>
#include"../inc/common.h"
void sigchld(int signum){
    for(;;){
        pid_t pid=waitpid(-1,0,WNOHANG);
        if(pid==-1){
            if(errno!=ECHILD){
                exit(-1);
            }
            break;
        }else if(!pid)
            break;
    }
}
