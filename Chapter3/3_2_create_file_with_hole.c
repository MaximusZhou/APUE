/*
	Create file with hole and test file size
	
	Example:
	$ls -l file.hole 
	-rw-r--r-- 1 gzzhougang gzzhougang 16394 12ÔÂ  9 21:11 file.hole
	$file file.hole 
	file.hole: data
	$od -c file.hole 
	0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
	0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
	*
	0040000   A   B   C   D   E   F   G   H   I   J
	0040012
	$ls -ls file.*
	8 -rw-r--r-- 1 gzzhougang gzzhougang 16394 12ÔÂ  9 21:19 file.hole
	20 -rw-r--r-- 1 gzzhougang gzzhougang 16394 12ÔÂ  9 21:19 file.nohole

	Analyse:
	the file.hole an file.nohole have different disk block.

*/

#include "../include/apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
char buf3[16394] = {0};

int main(void)
{
	int fd;
	if((fd = creat("file.hole",FILE_MODE)) < 0)
		err_sys("create error");
	
	if (write(fd,buf1,10) != 10)
		err_sys("buf1 write error");
	/*offset now = 10 */
	
	if (lseek(fd,16384, SEEK_SET) == -1)
		err_sys("lseek error");
	/*offset now = 16384 */

	if ( write(fd,buf2,10) != 10 )
		err_sys("buf2 write error");
	/*offset now = 16394 */
	
	close(fd);

	if((fd = creat("file.nohole",FILE_MODE)) < 0)
		err_sys("create error");

	if ( write(fd,buf3,16394) != 16394 )
		err_sys("buf3 write error");

	exit(0);
}
