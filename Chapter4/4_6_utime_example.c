/*
	utime function example
	
	Example:
	$ls -l foo bar    #display file modify time
	-rw-r--r-- 1 gzzhougang gzzhougang 0 12月 30 21:52 bar
	-rw-rwSrw- 1 gzzhougang gzzhougang 0 12月 30 21:52 foo
	$ls -lu foo bar   #display file access time
	-rw-r--r-- 1 gzzhougang gzzhougang 0 12月 30 21:52 bar
	-rw-rwSrw- 1 gzzhougang gzzhougang 0 12月 30 21:52 foo
	$./4_6_utime_example foo bar
	$ls -l foo bar
	-rw-r--r-- 1 gzzhougang gzzhougang 0 12月 30 21:52 bar
	-rw-rwSrw- 1 gzzhougang gzzhougang 0 12月 30 21:52 foo
	$ls -lu foo bar
	-rw-r--r-- 1 gzzhougang gzzhougang 0 12月 30 21:52 bar
	-rw-rwSrw- 1 gzzhougang gzzhougang 0 12月 30 21:52 foo
	$ls -lc foo bar     #display file stat node modify time
	-rw-r--r-- 1 gzzhougang gzzhougang 0  1月  7 21:56 bar
	-rw-rwSrw- 1 gzzhougang gzzhougang 0  1月  7 21:56 foo

	Analyse:
*/
#include "../include/apue.h"
#include <fcntl.h>
#include <utime.h>

int main(int argc, char *argv[])
{
	int       		i,fd;
	struct stat 	statbuf;
	struct utimbuf  timebuf;

	for (i = 1; i < argc; i ++)
	{
		if (stat(argv[i],&statbuf) < 0)
		{/*fetch current times*/
			err_ret("%s,stat error",argv[i]);
			continue;
		}

		if ((fd = open(argv[i],O_RDWR | O_TRUNC)) < 0 )
		{
			printf("zg");
			err_ret("%s,open error",argv[i]);
			continue;
		}

		close(fd);
		timebuf.actime = statbuf.st_atime;
		timebuf.modtime = statbuf.st_mtime;

		if (utime(argv[i],&timebuf) < 0)
		{/*reset times*/
			err_ret("%s,utime error",argv[i]);
			continue;
		}
	}
	exit(0);
}
