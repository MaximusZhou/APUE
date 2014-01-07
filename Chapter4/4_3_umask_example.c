/*
	umask function example
	
	Example:
	$umask
	0022
	$./4_3_umask_example 
	$ll foo bar
	-rw------- 1 gzzhougang gzzhougang 0 12ÔÂ 30 21:52 bar
	-rw-rw-rw- 1 gzzhougang gzzhougang 0 12ÔÂ 30 21:52 foo
	$umask
	0022

	Analyse:
*/
#include "../include/apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
int main(void)
{
	umask(0);	
	if (creat("foo",RWRWRW) < 0)
		err_sys("creat error for foo");
	
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar",RWRWRW) < 0)
		err_sys("creat error for bar");
	
	exit(0);
}
