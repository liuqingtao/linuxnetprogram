#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>

int main(){
    struct stat st;
    stat("a.txt",&st);
    printf("inode=%d\n",st.st_ino);
    printf("mode=%o\n",st.st_mode);
    printf("nlink=%d\n",st.st_nlink);
    printf("size=%d\n",st.st_size);
    printf("mtime=%s\n",ctime(&st.st_mtime));
    if(S_ISREG(st.st_mode)) printf("file\n");
    if(S_ISDIR(st.st_mode)) printf("dir\n");
    printf("权限：%o\n",st.st_mode&07777);
    return 0;
}