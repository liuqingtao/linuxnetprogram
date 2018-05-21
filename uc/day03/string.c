#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//关于字符串必须会的代码
int main(){
    //1 赋值 =改地址 strcpy（）改地址中的值
    char* s1="abc";
    char s2[4]="abc";
    s1="123";
    //s2="123";  //常指针不能用=赋值
    //strcpy(s1,"123"); //N 修改只读区
    strcpy(s2,"123");
    printf("s1=%s,s2=%s\n",s1,s2);

    char* s3=malloc(4);
   // s3="abc"; //s3指向只读区，内存泄露
    strcpy(s3,"abc");
    printf("s3=%s\n",s3);
    //free(s3);//free()只读区出错

    //2 比较字符串是否相等  ==比的是地址，strcmp比较的值
    char* s4="123";
    char* s5="123";
    char* s6=malloc(4);
    strcpy(s6,"123");
    if(s4==s5){
        printf("地址相等\n"); //Y
    }else{
        printf("不等\n");
    }
    if(s4==s6){
        printf("相等\n");
    }else{
        printf("地址不等\n"); //Y
    }
    if(strcmp(s4,s6)==0){
        printf("相等\n");//Y
    }else{
        printf("不等\n");
    }

    //3 字符串的大小和长度，数据的长度用strlen，内存容量用sizeof()
    
    char buf[100]={};
    strcpy(buf,"abcd");
    printf("length=%d\n",strlen(buf)); //数据的真实长度
    printf("size=%d\n",sizeof(buf));//内存的容量
    

    //4 字符串的拼接
    char* name="a.txt";
    char* path="/home/liuqingtao";
    char buf1[100]={};
   // strcpy(buf1,path);
    //strcat(buf1,"/");
    //strcat(buf1,name);
    sprintf(buf1,"%s/%s",path,name);//和上边一样的效果
    printf("buf1=%s\n",buf1);

    //5 用操作指针的方式编写字符串处理代码
    char* message="zhangfei,30";
    char sname[20]={};
    char age[10]={};
    int pos=10;//记录，的位置
    int flag=1;//标记，记录是写sname还是age
    int i;
    for(i=0;i<strlen(message);i++){
        if(*(message+i)==','){
            pos=i;
            flag=0;
            continue;
        }
        if(flag) sname[i]=*(message+i);
        else age[i-pos-1]=*(message+i);
    }
    printf("name=%s:age=%s\n",sname,age);

    //6 字符串和其他类型 （int/double）的转换
    //sprintf() 和sscanf()

    char* number="1234.5678";
    char buf2[10]={};
    double d=0.0;
    sscanf(number,"%lf",&d); //字符串转其他
    printf("d=%lf\n",d);
    sprintf(buf2,"%lf",&d); //其他转字符串
    printf("buf2=%s\n",buf2);

return 0;
}