#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main(){
    int i;
    /*
    FILE* file=fopen("num.txt","w");
    if(!file) perror("fopen"),exit(-1);
    for(i=0;i<1000000;i++){
        fwrite(&i,sizeof(i),1,file);
    }
    fclose(file);
    */
   int fd=open("num.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
   if(fd==-1) perror("open"),exit(-1);
   int arr[10000]={};
   for(i=0;i<1000000;i++){
       arr[i%10000]=i;
       if(i%10000==9999)
        write(fd,arr,sizeof(arr));
   }
   close(fd);
   return 0;
}