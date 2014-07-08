/*
	Example:
	$gcc -Wall 10_1_catch_signal_example.c  ../lib/error.c -o 10_1_catch_signal_example
	$./10_1_catch_signal_example  &
	[1] 54682
	$kill -USR1 54682
	received SIGUSR1
	$kill -USR2 54682
	received SIGUSR2
	$kill 54682      
	$
	[1]+  Terminated                  ./10_1_catch_signal_example

	Analyse:
*/

#include "../include/apue.h"

static void	sig_usr(int);	/* one handler for both signals */

int main(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR2");
	for ( ; ; )
		pause();
}

static void sig_usr(int signo)		/* argument is signal number */
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		err_dump("received signal %d\n", signo);
}
