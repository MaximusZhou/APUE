/* Traverse directory and count file type

	Example:

	$./4_7_traverse_dir ~/running/
	regular file  =   22620, 82.05 %
	directories   =    4938, 17.91 %
	block speical =       0,  0.00 %
	char speical  =       0,  0.00 %
	FIFOs         =       0,  0.00 %
	sockets       =       5,  0.02 %

	Analyse:
	note directory '.' and '..'

*/
#include "../include/apue.h"
#include <dirent.h>
#include <limits.h>

/*function type that is called for each filename*/
typedef int Myfunc(const char *, const struct stat *,int);

static Myfunc myfunc;
static int myftw(char *,Myfunc *);
static int dopath(Myfunc *);
char * path_alloc(int *sizep);

static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;
int main(int argc, char *argv[])
{
	int ret;

	if (argc != 2)
		err_quit("usage: ftw <starting-pathname>");
	ret = myftw(argv[1],myfunc);

	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if (ntot == 0)
		ntot = 1;  /*avoid divide by 0*/

	printf("regular file  = %7ld, %5.2f %%\n",nreg, nreg*100.0/ntot);
	printf("directories   = %7ld, %5.2f %%\n",ndir, ndir*100.0/ntot);
	printf("block speical = %7ld, %5.2f %%\n",nblk, nblk*100.0/ntot);
	printf("char speical  = %7ld, %5.2f %%\n",nchr, nchr*100.0/ntot);
	printf("FIFOs         = %7ld, %5.2f %%\n",nfifo, nfifo*100.0/ntot);
	printf("sockets       = %7ld, %5.2f %%\n",nsock, nsock*100.0/ntot);

	exit(ret);
}

/*
 *Descend through the hierarchy, starting at "pathname".
 *The caller's func() is called for every file.
 */

#define FTW_F 1   /*file other than directory*/
#define FTW_D 2   /*directory*/
#define FTW_DNR 3   /*directory than can't be read*/
#define FTW_NS 4   /*file that we can't stat*/

static char fullpath[PATH_MAX];   /*contains full pathname for every file*/

static int myftw(char *pathname, Myfunc *func)
{
	strcpy(fullpath,pathname);
	return(dopath(func));
}

/*Descend through the hierarchy, starting at "fullpath".
 *If "fullpath" is anything other than a directory, we lstat() it,
 *call func(), and return. For a directory, we call ourself
 *recursively for each name in the directory
 */

static int dopath(Myfunc *func)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR    *dp;
	int ret;
	char *ptr;

	if(lstat(fullpath,&statbuf) < 0)
		return(func(fullpath, &statbuf,FTW_NS));
	
	if (S_ISDIR(statbuf.st_mode) == 0)
		return(func(fullpath, &statbuf,FTW_F));  /*not a dirctory*/

	/*
	 * It's a dirctory. First call func() for the directory,
	 *then process each filename in the directory
	 */

	 if ((ret = func(fullpath,&statbuf,FTW_D)) != 0)
		 return ret;

	ptr = fullpath + strlen(fullpath);   /*point to end of fullpath*/
	*ptr = '/';
	ptr++;
	*ptr = 0;

	if((dp = opendir(fullpath)) == NULL)
		return(func(fullpath, &statbuf,FTW_DNR));

	while((dirp = readdir(dp)) != NULL)
	{
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 )
			continue;

		strcpy(ptr,dirp->d_name);  /*append name afther slash*/

		if((ret = dopath(func)) != 0 ) /*recursive*/
			break;
	}
	ptr[-1] = 0; /*erase everything from slash onwards*/

	if(closedir(dp) < 0)
		err_ret("can't not close directory %s",fullpath);

	return ret;
}


static int myfunc(const char *pathname, const struct stat *statptr,int type)
{
	switch(type)
	{
		case FTW_F:
			switch(statptr->st_mode & S_IFMT)
			{
				case S_IFREG: nreg++; break;
				case S_IFBLK: nblk++; break;
				case S_IFCHR: nchr++; break;
				case S_IFIFO: nfifo++; break; 
				case S_IFLNK: nslink++; break;
				case S_IFSOCK: nsock++; break;
				case S_IFDIR:
					err_dump("for S_IFDIR for %s",pathname);
			}
			break;

		case FTW_D:
			ndir++;
			break;

		case FTW_DNR:
			err_ret("can't read directory %s",pathname);
			break;

		case FTW_NS:
			err_ret("stat error for %s",pathname);
			break;

		default:
			err_dump("unknown type %d for pathname %s", type,pathname);
	}

	return(0);
}
