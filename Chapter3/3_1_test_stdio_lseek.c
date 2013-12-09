/*
	test lseek function for std file io 
*/
#include "../include/apue.h"

int main(void)
{
	if (lseek(STDIN_FILENO,0,SEEK_CUR) == -1) /*there is must be is equal operation*/
		printf("cannot seek\n");
	else
		printf("seek ok\n");
	
	exit(0);
}


