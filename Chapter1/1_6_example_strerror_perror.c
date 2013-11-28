/*
	example of strerror and perror 
*/
#include "../include/apue.h"
#include <asm-generic/errno-base.h> /*ENOENT*/
#include <arpa/tftp.h> /*EACCESS*/
#include <bits/errno.h>

int main(int argc,char *argv[])
{
	fprintf(stderr, "EACCESS: %s\n",strerror(EACCESS));
	
	/*errno = ENOENT;*/
	perror(argv[0]);
	exit(0);
}
