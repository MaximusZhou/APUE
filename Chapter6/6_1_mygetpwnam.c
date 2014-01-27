/*
	
	Example:
	$./6_1_mygetpwnam 
	name=gzzhougang,passwd=x,uid=1011,gid=1011,dir=/home/gzzhougang,shell=/bin/bash

	Analyse:
	/usr/include/pwd.h
	struct passwd
	{
	  char *pw_name;		
	  char *pw_passwd;		
	  __uid_t pw_uid;		
	  __gid_t pw_gid;		
	  char *pw_gecos;		
	  char *pw_dir;			
	  char *pw_shell;		
	};

*/
#include "../include/apue.h"
#include <pwd.h>

struct passwd *mygetpwnam(char *);

int main(void)
{
	int uid = getuid();
	struct passwd *pwd = getpwuid(uid);
	char *name = pwd->pw_name;

	struct passwd *res = mygetpwnam(name);

	printf("name=%s,passwd=%s,uid=%d,gid=%d,dir=%s,shell=%s\n",
			res->pw_name,res->pw_passwd,res->pw_uid,res->pw_gid,res->pw_dir,res->pw_shell);

	exit(0);
}

struct passwd *mygetpwnam(char *name)
{
	struct passwd *ptr;

	setpwent();
	while((ptr = getpwent()) != NULL)
		if(strcmp(name,ptr->pw_name) == 0)
			break;

	endpwent();

	return(ptr);
}

