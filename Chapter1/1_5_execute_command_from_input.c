/*
	execute command from input
*/
#include "../include/apue.h"
#include <sys/wait.h>

int main(void)
{
	char buf[MAXLINE];
	pid_t pid;
	int status;
	int cur_buff_len;

	printf("%% "); 
	while(fgets(buf,MAXLINE,stdin) != NULL)
	{
		cur_buff_len = strlen(buf);
		if (buf[cur_buff_len - 1] == '\n')
			buf[cur_buff_len - 1] = 0;

		if ((pid = fork()) < 0)
		{
			err_sys("fork error");
		}
		else if (pid == 0)
		{
			execlp(buf,buf,(char*)0);
			err_ret("can't execute:%s",buf);
			exit(127);
		}

		/*parent*/
		if ((pid = waitpid(pid,&status,0)) < 0 )
			err_sys("waitpid error");

		printf("%% "); 
	}

	exit(0);
}
