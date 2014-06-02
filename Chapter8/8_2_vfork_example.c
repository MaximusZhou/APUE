/*
	
	Example:
	$./8_2_vfork_example 
	before fork
	pid = 41437, glob = 6, var = 88
	Analyse:
	the incrementing of the variables done by the child changes the values in the parent.
	Because the child runs in the address space of the parent, this doesn 't surprise us.
	This behavior, however, differs fro m fork. 

*/

#include "../include/apue.h"

int		glob = 6;		/* external variable in initialized data */
int main(void)
{
	int		var;		/* automatic variable on the stack */
	pid_t	pid;

	var = 88;
	printf("before fork\n");	/* we don't flush stdout */
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {		/* child */
		glob++;					/* modify variables */
		var++;
		_exit(0);               /*Not exit,or undefined*/
	}
	/*
	*Parent continus here
	*/
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	exit(0);
}
