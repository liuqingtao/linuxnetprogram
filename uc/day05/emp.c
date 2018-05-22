#include "emp.h"

int main(){
    struct emp employee;
    printf("input the id name sal\n");
    scanf("%d%s%lf",&employee.id,&employee.name,&employee.sal);
    int fd=open("emp.txt",O_RDWR|O_CREAT|O_APPEND,0666);
    if(fd==-1) perror("open"),exit(-1);
    char buff[100]={};
    sprintf(buff,"%d,%s,%lf",employee.id,employee.name,employee.sal);
    int res=write(fd,buff,strlen(buff));
    if(res==-1) perror("write"),exit(-1);
    printf("add success\n");
    close(fd);   

    int fdo=open("emp.txt",O_RDONLY);
    if(fdo==-1) perror("open"),exit(-1);
    struct emp em;
    while(1){
        int res=read(fd,&em,sizeof(em));
        if(res==-1) perror("read"),exit(-1);
        if(!res) break;
        printf("%d %s %lf\n",em.id,em.name,em.sal);
    }  
    close(fdo);
}
