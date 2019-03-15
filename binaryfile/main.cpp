/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  二进制读写的测试
 *
 *        Version:  1.0
 *        Created:  2015年06月26日 08时55分26秒
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
#include	<stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned int read_pos;


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  fileOperate
 *  Description:  写文件
 *		  Param:  pszFileName 文件名称
 *				  pszBuf 要写入的缓冲区
 *				  len	要写入的长度
 *		 Return:  写入的长度
 * =====================================================================================
 */
unsigned int writeFile ( char *pszFileName, unsigned char *pszBuf, int len)
{
	FILE *pFile = NULL;
	unsigned int num;

	pFile = fopen( pszFileName, "ab+" );
	if( NULL == pFile )
	{
		perror( "pszFileName" );
		return 0;
	}


	num = fwrite( pszBuf, 1, len, pFile  );

	fclose( pFile );

	return num;
}		/* -----  end of function fileOperate  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  readFile
 *  Description:  读文件
 *		  Param:  pszFileName 文件名
 *				  pszBuf 读出缓冲区
 *				  len 长度
 *		 Return:  读出的长度
 * =====================================================================================
 */
unsigned int readFile ( char *pszFileName, unsigned char *pszBuf, int len )
{
	FILE *pFile = NULL;
	int num=0;

	pFile = fopen( pszFileName, "rb" );
	if( NULL == pFile )
	{
		perror( "pszFileName" );
		return 0;
	}

	if( -1 == fseek( pFile, read_pos, SEEK_SET ) )
	{
		return 0;
	}

	num = fread( pszBuf, 1, len, pFile  );

	read_pos += num;

	fclose( pFile );

	return num;
}		/* -----  end of function readFile  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  文件试写 调有形式 ./main 文件名;
 *		  Param:
 *		 Return:
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{

	unsigned char szRBuf[1024];
	unsigned char szBuf[1024]  ;
	unsigned read_num = 0;
	for( int i=0; i<1024; i++ )
	{
		szBuf[i] = ( i%256);
	}

	if( argc >= 2 )
	{
		writeFile ( argv[1], szBuf, 1024 );

		read_pos = 0;

		while ( ( read_num = ( readFile( argv[1], szRBuf, 128 ) ) ) > 0 )
		{
			for( int i=0; i<128; i++ )
			{
				printf ( "%.2x ", szRBuf[i] );
			}
			printf ( "\n" );
		}

	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
