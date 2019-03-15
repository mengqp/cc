/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *       Compiler:  gcc
 *
 *        Version:  1.0
 *        Created:  2015年10月12日 16时22分27秒
 *
 *         Author:  mengqp 
 *   Organization:  
 *
 *		  history:
 * =====================================================================================
 */
#include <stdio.h>

#include	<stdlib.h>
#include <string.h>
#include "GroupBroad.h"
#include <unistd.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 *		  Param:
 *		 Return:
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	unsigned char uchBuf[256] = "wqivb";
	unsigned char uchBuf1[256] = "";
	int len = 0;
	int len1 = 0;
	len = strlen( (char *)uchBuf );
	printf ( "hello\n" );
	while(1 )
	{
		if( 0 == GroupBroadInit (  ))
		{
			printf ( "GroupBroadInit succ\n" );
		}
		sleep( 1 );
		GroupBroadRecv( uchBuf1, &len1 );
		if( len1 > 0 )
		{
			printf ( "uchBuf1=%s\n", uchBuf1 );
			len1 = 0;
			memset( uchBuf1, 0, 256 );
			GroupBroadSend( uchBuf1, len1 ) ;
		}
		else
		{
			printf ( "recv null %s\n", uchBuf1 );
			sleep( 1 );

		}
		printf ( "uchBuf1=%s\n", uchBuf1 );

	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
