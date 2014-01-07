/*
	access function example
	
	Example:
	$ls -l bar foo
	-rw------- 1 gzzhougang gzzhougang 0 12月 30 21:52 bar
	-rw-rw-rw- 1 gzzhougang gzzhougang 0 12月 30 21:52 foo
	$./4_4_chmod_example 
	$ls -l bar foo       
	-rw-r--r-- 1 gzzhougang gzzhougang 0 12月 30 21:52 bar
	-rw-rwSrw- 1 gzzhougang gzzhougang 0 12月 30 21:52 foo

	Analyse:
*/
#include "../include/apue.h"
int main(void)
{
	struct stat statbuf;

	/*turn on set-group-ID and turn off group-execute*/
	if (stat("foo",&statbuf) < 0 )
		err_sys("stat error for foo");
	if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		err_sys("chmod error for foo");

	/*set absolute mode to "rw-r--r--"*/
	if (chmod("bar",S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))
		err_sys("chmod error for bar");
	
	exit(0);
}
