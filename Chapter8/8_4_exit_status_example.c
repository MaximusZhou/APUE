/*
	
	Example:

	$gcc -Wall 8_4_exit_status_example.c  ../lib/error.c  -o 8_4_exit_status_example
	8_4_exit_status_example.c: In function 'main':
	8_4_exit_status_example.c:54: warning: division by zero
	$./8_4_exit_status_example 
	normal termination, exit status =  7
	abnormal termination, signal number  = 6 (nocorefile)
	abnormal termination, signal number  = 8 (nocorefile)
	Analyse:
	there is no portable way to map the signal numbers from  WTERMSIG  into descriptive names.
	We have to look at the  <signal.h> header to verify that  SIGABRT has a value of 
	6 and that SIGFPE  has a value of 8. 
*/

#include "../include/apue.h"
#include <sys/wait.h>

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
	pid_t pid;
	int status;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)              /* child */
		exit(7);

	if (wait(&status) != pid)       /* wait for chi ld */ 
		err_sys("wait error"); 
	pr_exit(status);                /* and print it s status */ 

	if ((pid = fork()) < 0) 
		err_sys("fork error"); 
	else if (pid == 0)              /* child */ 
		abort();                    /* generates SI GABRT */ 

	if (wait(&status) != pid)       /* wait for chi ld */ 
		err_sys("wait error"); 
	pr_exit(status);                /* and print it s status */ 

	if ((pid = fork()) < 0) 
		err_sys("fork error"); 
	else if (pid == 0)              /* child */ 
		status /= 0;                /* divide by 0  generates SIGFPE */ 

	if (wait(&status) != pid)       /* wait for chi ld */ 
		err_sys("wait error"); 
	pr_exit(status);                /* and print it s status */ 

	exit(0); 
}

