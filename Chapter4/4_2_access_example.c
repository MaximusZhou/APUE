/*
	access function example
	
	Example:
	$ll ./4_2_access_example
	-rwxr-xr-x 1 gzzhougang gzzhougang 10741 12ÔÂ 30 20:53 ./4_2_access_example
	$./4_2_access_example 4_2_access_example
	read access ok
	open for reading ok
	$ll /etc/passwd
	-rw-r--r-- 1 root root 2253  9ÔÂ 12 09:57 /etc/passwd
	$./4_2_access_example /etc/passwd
	read access ok
	open for reading ok
	$ll /etc/shadow
	-rw-r----- 1 root shadow 2801  9ÔÂ 12 12:51 /etc/shadow
	$./4_2_access_example /etc/shadow
	access error for /etc/shadow: Permission denied
	open error for /etc/shadow: Permission denied

	Analyse:
*/
#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("useage:4_2_access_example <pathname>");

	if (access(argv[1],R_OK) < 0)
		err_ret("access error for %s",argv[1]);
	else
		printf("read access ok\n");

	if (open(argv[1],O_RDONLY) < 0)
		err_ret("open error for %s",argv[1]);
	else
		printf("open for reading ok\n");
	
	exit(0);
}
