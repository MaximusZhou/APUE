/*
	Example:
	$gcc -Wall 11_1_print_thread_id.c  -lpthread ../lib/error.c -o 11_1_print_thread_id
	$./11_1_print_thread_id 
	main thread: pid 24946 tid 3617482496 (0xd79e6700)
	new thread:  pid 24946 tid 3609552640 (0xd7256700)
	$ldd ./11_1_print_thread_id
	        linux-vdso.so.1 =>  (0x00007fff059ff000)
			libpthread.so.0 => /lib/libpthread.so.0 (0x00007fe38725c000)
			libc.so.6 => /lib/libc.so.6 (0x00007fe386efa000)
			/lib64/ld-linux-x86-64.so.2 (0x00007fe387482000)
	Analyse:
*/

#include "../include/apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
	  (unsigned int)tid, (unsigned int)tid);
}

void* thr_fn(void *arg)
{
	printids("new thread: ");
	return((void *)0);
}

int main(void)
{
	int		err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0)
		err_quit("can't create thread: %s\n", strerror(err));
	printids("main thread:");
	sleep(1);
	exit(0);
}
