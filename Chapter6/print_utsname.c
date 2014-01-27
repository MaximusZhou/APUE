/*
	
	Example:
	$./print_utsname 
	sysname:Linux,nodename:onlinegame10-63,release:2.6.32-5-amd64,version:#1 SMP Fri May 10 08:43:19 UTC 2013,machine:x86_64
	$uname -a
	Linux onlinegame10-63 2.6.32-5-amd64 #1 SMP Fri May 10 08:43:19 UTC 2013 x86_64 GNU/Linux

	Analyse:
*/
#include "../include/apue.h"
#include <sys/utsname.h>

int main(void)
{
	struct utsname sysinfo;
	if (uname(&sysinfo) < 0)
		err_sys("uanme error");

	printf("sysname:%s,nodename:%s,release:%s,version:%s,machine:%s\n",
			sysinfo.sysname,sysinfo.nodename,sysinfo.release,sysinfo.version,sysinfo.machine);
	exit(0);
}
