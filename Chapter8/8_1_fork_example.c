/*
	
	Example:
	$gcc -Wall 8_1_fork_example.c ../lib/error.c  -o 8_1_fork_example
	$./8_1_fork_example 
	a write to stdout
	before fork
	pid = 41763, glob = 7, var = 89
	pid = 41762, glob = 6, var = 88
	$./8_1_fork_example > temp.out
	$cat temp.out
	a write to stdout
	before fork
	pid = 41873, glob = 7, var = 89
	before fork
	pid = 41872, glob = 6, var = 88
	Analyse:
	Note buffer data.
*/

#include "../include/apue.h"

int		glob = 6;		/* external variable in initialized data */
char	buf[] = "a write to stdout\n";

int main(void)
{
	int		var;		/* automatic variable on the stack */
	pid_t	pid;

	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error");
	printf("before fork\n");	/* we don't flush stdout */

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {		/* child */
		glob++;					/* modify variables */
		var++;
	} else {
		sleep(2);				/* parent */
	}

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	exit(0);
}
