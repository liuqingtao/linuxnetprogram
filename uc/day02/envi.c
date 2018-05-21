#include<stdio.h>
#include<stdlib.h>
int main(){
	extern char** environ;
	char ** p=environ;

	while(*p){
		printf("%s\n",*p);
		p++;
		//*p++;
		//**p++;
	}

}
