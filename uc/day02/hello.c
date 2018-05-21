#include<stdio.h>
#pragma GCC poison goto
int main(){
	goto OK;
	printf("hello world!");
OK:printf("test");	
	return 0;
}
