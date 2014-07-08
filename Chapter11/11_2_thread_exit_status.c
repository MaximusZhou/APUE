/*
	Example:
	$gcc -Wall 11_2_thread_exit_status.c  -lpthread ../lib/error.c -o 11_2_thread_exit_status
	$./11_2_thread_exit_status 
	thread 2 exiting
	thread 1 returning
	thread 1 exit code 0x1
	thread 2 exit code 0x2
	Analyse:
	the exit status of a thread can be obtained by another thread by calling pthread_join.
*/

#include "../include/apue.h"
#include <pthread.h>

void *thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
	return((void *)1);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 exiting\n");
	pthread_exit((void *)2);
}

int main(void)
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		err_quit("can't create thread 1: %s\n", strerror(err));
	
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		err_quit("can't create thread 2: %s\n", strerror(err));
	
	err = pthread_join(tid1, &tret);
	if (err != 0)
		err_quit("can't join with thread 1: %s\n", strerror(err));
	printf("thread 1 exit code %p\n", tret);

	err = pthread_join(tid2, &tret);
	if (err != 0)
		err_quit("can't join with thread 2: %s\n", strerror(err));
	printf("thread 2 exit code %p\n", tret);

	exit(0);
}
