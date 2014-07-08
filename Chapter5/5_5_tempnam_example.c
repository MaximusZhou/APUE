/*
	
	Example:

	Analyse:
*/
#include "../include/apue.h"

int main(int argc, char *argv[])
{
	if (argc != 3)
		err_quit("usage: 5_5_tempnam_example <directoy> <prefix>");

	printf("%s\n", \
		tempnam(argv[1][0] != ' ' ? argv[1][0]: NULL,argv[2][0] != ' ' ? argv[2][0]: NULL));

	exit(0);
}
