/*
	std output from std input
*/
#include "../include/apue.h"
int main(void)
{
	int c;

	/*while input enter key,the function read() begin read data(include "\n")*/
	while((c = getc(stdin)) != EOF)
		if (putc(c,stdout) == EOF)
			err_sys("output error");

	/*ferror()
	Checks if the error indicator associated with stream is set,
	returning a value different from zero if it is.
	This indicator is generally set by a previous operation on the stream that failed,
	and is cleared by a call to clearerr, rewind or freopen.
	*/
	if (ferror(stdin))
		err_sys("input error");
	
	exit(0);
}
