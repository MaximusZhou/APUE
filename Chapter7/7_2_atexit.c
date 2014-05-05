/*
	
	Example:
	$gcc -Wall 7_2_atexit.c ../lib/error.c -o 7_2_atexit
	$./7_2_atexit 
	first exit handle
	first exit handle
	second exit handle

	Analyse:
	The exit function calls these function in reverse order of their registation.
	Each function is called as many times as it was registed.
*/

#include "../include/apue.h"
#include <pwd.h>

static void my_exit1(void);
static void my_exit2(void);

int main(void)
{
	if (atexit(my_exit2) != 0)
		err_sys("can't register my_exit2");

	if (atexit(my_exit1) != 0)
		err_sys("can't register my_exit1");

	if (atexit(my_exit1) != 0)
		err_sys("can't register my_exit1");
	
	return 0;
}

static void my_exit1(void)
{
	printf("first exit handle\n");
}

static void my_exit2(void)
{
	printf("second exit handle\n");
}
