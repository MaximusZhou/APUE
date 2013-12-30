/*
	print file type in command line paraments
	
	Example:
	$./4_1_printf_file_type /etc/passwd /etc/ /dev/initctl /dev/log /dev/tty 
	/etc/passwd: regular 
	/etc/: directory 
	/dev/initctl: fifo 
	/dev/log: socket 
	/dev/tty: character special

	Analyse:
*/
#include "../include/apue.h"

int main(int argc, char *argv[])
{
	int i;
	struct stat buf;
	char *ptr;

	for(i = 1; i < argc; i++)
	{
		printf("%s: ",argv[i]);
		if ( lstat(argv[i],&buf) < 0 ) 
		{
			err_ret("lstat error");
			continue;
		}

		if (S_ISREG(buf.st_mode))
			ptr = "regular";
		else if (S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if (S_ISCHR(buf.st_mode))
			ptr = "character special";
		else if (S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if (S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else if (S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";
		
		printf("%s \n",ptr);
	}

	exit(0);
}
