/*
	Example:
	$gcc -Wall 8_12_implement_system_function.c  ../lib/error.c -o 8_12_implement_system_function
	Analyse:
*/


#include "../include/apue.h"
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int system(const char *cmdstring)	/* version without signal handling */
{
	pid_t	pid;
	int		status;

	if (cmdstring == NULL)
		return(1);		/* always a command processor with UNIX */

	if ((pid = fork()) < 0) {
		status = -1;	/* probably out of processes */
	} else if (pid == 0) {				/* child */
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(127);		/* execl error */
	} else {							/* parent */
		while (waitpid(pid, &status, 0) < 0) {
			if (errno != EINTR) {
				status = -1; /* error other than EINTR from waitpid() */
				break;
			}
		}
	}

	return(status);
}

void pr_exit(int status) 
{ 
	if (WIFEXITED(status)) 
		printf("normal termination, exit status = % d\n", 
				WEXITSTATUS(status)); 
	else if (WIFSIGNALED(status)) 
		printf("abnormal termination, signal number  = %d%s\n", 
				WTERMSIG(status), 
#ifdef  WCOREDUMP 
				WCOREDUMP(status) ? " (core file ge nerated)" : "");  
#else 
				" (nocorefile)"); 
#endif 
	else if (WIFSTOPPED(status)) 
		printf("child stopped, signal number = %d\n ", 
				WSTOPSIG(status)); 
} 

int main(void)
{
	int		status;

	if ((status = system("date")) < 0)
		err_sys("system() error");
	pr_exit(status);

	if ((status = system("nosuchcommand")) < 0)
		err_sys("system() error");
	pr_exit(status);

	if ((status = system("who; exit 44")) < 0)
		err_sys("system() error");
	pr_exit(status);

	exit(0);
}
