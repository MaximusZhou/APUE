/*
	Analyse:

	z for type size_t
	sizeof include null in str
	strlen exclude null in str
*/
#include "../include/apue.h"

int main(int argc, char *argv[])
{
	char *s = "abcde";
	char t[] = "abcde";

	printf("sizeof:%ld,%ld\n",sizeof(s),sizeof(t)); /*output : sizeof:8,6*/
	printf("strlen:%zd,%zd\n",strlen(s),strlen(t)); /*output : strlen:5,5*/

	exit(0);
}
