/* chdir function example

	Example:
	$pwd
	/home/gzzhougang/github/APUE/Chapter4
	$./4_8_chdir_example 
	current working dir:/tmp
	$pwd
	/home/gzzhougang/github/APUE/Chapter4

	Analyse:
	the function chdir only change the working directory of the current process
	,and the function can not change the working dirctory of the parent process
*/

#include "../include/apue.h"
#include <limits.h>

int main(void)
{
	char path_name[PATH_MAX];
	if (chdir("/tmp") < 0)
		err_sys("chdir failed");

	getcwd(path_name,PATH_MAX);
	printf("current working dir:%s\n",path_name);
	exit(0);
}
