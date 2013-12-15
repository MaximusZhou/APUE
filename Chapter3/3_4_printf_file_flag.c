/*
	print file flag
	
	Example:
	$./3_4_printf_file_flag 0 
	read write
	$./3_4_printf_file_flag 1
	read write
	$./3_4_printf_file_flag 2
	read write
	$./3_4_printf_file_flag 0 <  /dev/tty  
	read only
	$./3_4_printf_file_flag 1 >  temp.foo  
	$cat temp.foo 
	write only
	$./3_4_printf_file_flag 2 >>  temp.foo 
	$cat temp.foo 
	write only
	read write
	$./3_4_printf_file_flag 2 2>>  temp.foo
	write only,append
	$cat temp.foo 
	write only
	read write
	$./3_4_printf_file_flag 5 5<>temp.foo      
	read write

	Analyse:
	5<>temp.foo is meaning that opening the file temp.foo with mode read and write
	$./3_4_printf_file_flag 1 >  temp.foo is meaning that: the file temp.foo is existed,
	so the file be created by the write only way,and the fd 1 is redicted to the file.
*/

#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int val;
	if (argc != 2)
		err_quit("usage: 3_4_printf_file_flag <descriptor#>");
	
	if ((val = fcntl(atoi(argv[1]),F_GETFL,0)) < 0)
		err_sys("fcntl error for fd %d",atoi(argv[1]));

	switch(val & O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only");
			break;
		
		case O_WRONLY:
			printf("write only");
			break;

		case O_RDWR:
			printf("read write");
			break;

		default:
			err_dump("unkown access mode");
	}

	if (val & O_APPEND)
		printf(",append");

	if (val & O_NONBLOCK)
		printf(",noblocking");

#if defined(O_SYNC)
	if (val & O_SYNC)
		printf(", synchronous writes");
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
		if (val & O_FSYNC)
			printf(", synchronous writes");
#endif
		
		putchar('\n');
		exit(0);
}
