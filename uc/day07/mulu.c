#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
//递归打印出当前目录和子目录的子项
//思路：先打印当前目录，判断子项是否为目录
//如果是目录打印后递归;否则打印

void print(char* path){
    DIR* dir=opendir(path);
    if(dir==NULL) return;
    struct dirent* ent;
    while(ent=readdir(dir)){
        if(strcmp(ent->d_name,".")==0||
            strcmp(ent->d_name,"..")==0)
            continue;
        if(ent->d_type==4){//子项是目录
            printf("[%s]\n",ent->d_name);
            char buff[100]={};
            sprintf(buff,"%s/%s",path,ent->d_name);
            print(buff);//递归
        }else{//不是目录
            printf("%s\n",ent->d_name);
        }
    }
}

int main(){
    print("../");//要求打印所有内容（子目录）
}