/*
 * @Author: lqt 
 * @Date: 2018-04-24 15:07:43 
 * @Last Modified by: lqt
 * @Last Modified time: 2018-04-24 16:08:23
 */

#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include<cstdio>
#include<cstdlib>
#include<string.h>
#include<fcntl.h>

typedef struct stu
{
    char name[4];
    int age;
}STU;

#define ERR_EXIT(m)\
do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"usage:%s <file>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    int fd;
    fd=open(argv[1],O_CREAT|O_RDWR|O_TRUNC,0666);
    if(fd==-1)
        ERR_EXIT("open");
    lseek(fd,sizeof(STU)*5-1,SEEK_SET);
    write(fd,"",1);
    STU *p;
    p=(STU *)mmap(NULL,sizeof(STU)*5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==NULL)
        ERR_EXIT("mmap");
    char ch='a';
    int i;
    for(i=0;i<=5;i++)
    {
        memcpy((p+i)->name,&ch,1);
        (p+i)->age=20+i;
        ch+=1;
    }
    printf("initialize over");
    munmap(p,sizeof(STU)*5);
    return 0;
}
