/* st_dev and st_rdev value example

	Example:
	$./4_9_st_dev_example / /home/gzzhougang/ /dev/tty[01]
	/:dev = 8/1
	/home/gzzhougang/:dev = 8/9
	/dev/tty0:dev = 0/5(character) rdev = 4/0
	/dev/tty1:dev = 0/5(character) rdev = 4/1
	$mount
	/dev/sda1 on / type ext3 (rw,errors=remount-ro)
	/dev/sda9 on /home type ext3 (rw,noatime)
	$ls -lL /dev/tty[01] /dev/sda8 /dev/sda5
	brw-rw---- 1 root disk 8, 5 12月  2 23:47 /dev/sda5
	brw-rw---- 1 root disk 8, 8 12月  2 23:48 /dev/sda8
	crw------- 1 root root 4, 0 12月  3 07:47 /dev/tty0
	crw------- 1 root root 4, 1 12月  3 00:06 /dev/tty1

	Analyse:
	Only character and block device have st_rdev, st_rdev include real dev number. 

*/

#include "../include/apue.h"
#include "/usr/include/linux/kdev_t.h"

int main(int argc, char *argv[])
{
	int  i;
	struct stat buf;

	for(i = 1; i < argc; i ++)
	{
		printf("%s:",argv[i]);

		if (stat(argv[i],&buf) < 0)
		{
			err_ret("stat error");
			continue;
		}

		printf("dev = %d/%d",MAJOR(buf.st_dev),MINOR(buf.st_dev));
		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		{
			printf("(%s) rdev = %d/%d",
						    (S_ISCHR(buf.st_mode)) ? "character" : "block",
							MAJOR(buf.st_rdev),MINOR(buf.st_rdev));
		}
		printf("\n");
			
	}

	exit(0);
}
