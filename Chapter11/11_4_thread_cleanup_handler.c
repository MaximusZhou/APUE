/*
	Example:
	$gcc -Wall 11_4_thread_cleanup_handler.c  -lpthread ../lib/error.c -o 11_4_thread_cleanup_handler
	$./11_4_thread_cleanup_handler 
	thread 1 start
	thread 1 push complete
	thread 2 start
	thread 2 push complete
	thread 1 exit code 1
	cleanup: thread 2 second handler
	cleanup: thread 2 first handler
	thread 2 exit code 2

	Analyse:
	when the thread performs one of the following  actions:
		Makes a call to pthread_exit 
		Responds to a cancellation request
		Makes a call to pthread_cleanup_pop with a nonzero execute argument 
	
		A restriction with these functions(pthread_cleanup_pop and pthread_cleanup_push) is that,
		because they can be implemented as macros, they must be used in matched pairs within the 
		same scope in a thread. Th e macro definition of  pthread_cleanup_push can include a { 
		character, in which case the matching } character is in the pthread_cleanup_pop definition. 
*/

#include "../include/apue.h"
#include <pthread.h>

void
cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}

void *
thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg)
		return((void *)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return((void *)1);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	if (arg)
		pthread_exit((void *)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

int
main(void)
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if (err != 0)
		err_quit("can't create thread 1: %s\n", strerror(err));

	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	if (err != 0)
		err_quit("can't create thread 2: %s\n", strerror(err));

	err = pthread_join(tid1, &tret);
	if (err != 0)
		err_quit("can't join with thread 1: %s\n", strerror(err));
	printf("thread 1 exit code %d\n", (int)tret);

	err = pthread_join(tid2, &tret);
	if (err != 0)
		err_quit("can't join with thread 2: %s\n", strerror(err));
	printf("thread 2 exit code %d\n", (int)tret);
	exit(0);
}
