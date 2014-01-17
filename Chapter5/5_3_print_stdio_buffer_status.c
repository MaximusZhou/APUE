/*
	
	Example:
	$./5_3_print_stdio_buffer_status 
	enter any character
	a
	one line to standard error
	stream = stdin, line buffered, buffer size = 1024
	stream = stdout, line buffered, buffer size = 1024
	stream = stderr, unbuffered, buffer size = 1
	stream = /etc/motd, fullly buffered, buffer size = 4096
	$./5_3_print_stdio_buffer_status < /etc/terminfo/README >std.out 2>std.err
	gzzhougang:~/github/APUE/Chapter5$cat std.err 
	one line to standard error
	gzzhougang:~/github/APUE/Chapter5$cat std.out 
	enter any character
	stream = stdin, fullly buffered, buffer size = 4096
	stream = stdout, fullly buffered, buffer size = 4096
	stream = stderr, unbuffered, buffer size = 1
	stream = /etc/motd, fullly buffered, buffer size = 4096

	Analyse:
*/
#include "../include/apue.h"

void pre_stdio(const char*, FILE*);

int main(void)
{
	FILE *fp;
	fputs("enter any character\n",stdout);
	if (getchar() == EOF)
		err_sys("getchar error");
	fputs("one line to standard error\n",stderr);

	pre_stdio("stdin",stdin);
	pre_stdio("stdout",stdout);
	pre_stdio("stderr",stderr);

	if((fp = fopen("/etc/motd","r")) == NULL)
		err_sys("fopen error");
	
	if (getc(fp) == EOF)
		err_sys("getc error");

	pre_stdio("/etc/motd",fp);

	exit(0);
}

void pre_stdio(const char *name,FILE *fp)
{
	printf("stream = %s, ",name);

	if(fp->__IO_file_flags & _IO_UNBUFFERED )
		printf("unbuffered");
	else if(fp->_flags & _IO_LINE_BUF )
		printf("line buffered");
	else
		printf("fullly buffered");
	
	printf(", buffer size = %ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
}
