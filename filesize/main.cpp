/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年07月01日 14时25分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mengqp 
 *   Organization:  
 *
 *		  history:
 * =====================================================================================
 */

#include <stdio.h> 
#include <dirent.h> 
#include <sys/stat.h> 
#include <stdlib.h>
#include <ftw.h>
#include <unistd.h>  

static unsigned int totalsize;

static int CalDirSize( const char *pPath, const struct stat *s, int flagtype   )
{
	printf ( "设备号:%llu 节点号:%lu 大小:%lu\n",
			s->st_dev,  s->st_ino, s->st_size );
	totalsize += s->st_size;
	return 0;
}
 
//执行方式	./main path
int main(int argc, char **argv) 
{ 
	int exists; 
	totalsize = 0;

	//执行方式	./main path
	if( 2 != argc )
	{
		printf ( "argc=%d != 2 is not right\n", argc );
	}

    if (!argv[1] || access(argv[1], R_OK))  
	{
		printf ( "%s is not a dirpath\n", argv[1] );
		return -1;	
	}

	exists = ftw( argv[1], CalDirSize, 20 );
	if( 0 ==  exists)
	{
		printf ( "path = %s totalsize= %d\n",
				argv[1], totalsize );
	}

	return 0;
}
