/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  zr
 *
 *        Version:  1.0
 *        Created:  2015年09月24日 14时30分58秒
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
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h> 
#include <stdlib.h>
#include <ftw.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


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
static unsigned int writeTobFile ( char *pszFileName, unsigned char *pszBuf, int len)
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
unsigned int readFrombFile ( char *pszFileName, unsigned char *pszBuf, int len, unsigned int &uiReadpos )
{
	FILE *pFile = NULL;
	int num=0;

	pFile = fopen( pszFileName, "rb" );
	if( NULL == pFile )
	{
		perror( "pszFileName" );
		return 0;
	}

	if( -1 == fseek( pFile, uiReadpos, SEEK_SET ) )
	{
		fclose( pFile );
		return 0;
	}

	num = fread( pszBuf, 1, len, pFile  );

	uiReadpos += num;

	fclose( pFile );

	return num;
}		/* -----  end of function readFile  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GetFileSize
 *  Description:  获取文件大小
 *		  Param:  pchFileName:文件名
 *		 Return:  大小 0为失败
 * =====================================================================================
 */
unsigned long GetFileSize ( const char *pchFileName )
{
	unsigned long filesize = 0;	
	struct stat statbuff;

	if(stat(pchFileName, &statbuff) < 0)
	{
		return filesize; 
	}
	else
	{
		filesize = statbuff.st_size;
	}

	return filesize;
}		/* -----  end of function GetFileSize  ----- */


static unsigned int uiTotalSize = 0;
static int CalDirSize( const char *pPath, const struct stat *s, int flagtype   )
{
	printf ( "设备号:%llu 节点号:%lu 大小:%lu\n",
			s->st_dev,  s->st_ino, s->st_size );
	uiTotalSize += s->st_size;
	return 0;
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GetDirSize
 *  Description:  获取文件夹下所有文件大小 
 *		  Param:  pszDirPath:目录
 *		 Return:  目录内文件大小
 * =====================================================================================
 */
unsigned int GetDirSize ( char *pszDirPath )
{
	int iRtn;
	uiTotalSize = 0;

    if (NULL == pszDirPath || access(pszDirPath, R_OK))  
	{
		printf ( "%s is not a dirpath\n", pszDirPath );
		return -1;	
	}

	iRtn = ftw( pszDirPath, CalDirSize, 20 );
	if( 0 ==  iRtn)
	{
		// printf ( "path = %s totalsize= %d\n",
				// pszDirPath,  uiTotalSize );
	}

	return uiTotalSize;
}		/* -----  end of function GetDirSize  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  IsFileExist
 *  Description:  查看文件是否存在
 *		  Param:  pchFileName:文件
 *		 Return:
 * =====================================================================================
 */
bool IsFileExist ( const char *pchFileName )
{
    struct stat statbuf;
    if(lstat(pchFileName, &statbuf) ==0)
	{
        return S_ISREG(statbuf.st_mode) != 0;//判断文件是否为常规文件
	}
    return false;
	// if( NULL == pchFileName )
	// {
		// return false;
	// }

	// if( 0 == access( pchFileName, F_OK ) )
	// {
		// return true;
	// }

	// return false;
}		/* -----  end of function IsFileExist  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  IsDirExist
 *  Description:  
 *		  Param:
 *		 Return:
 * =====================================================================================
 */
bool IsDirExist ( const char *pchDirPath )
{
	// if( NULL == pchDirPath )
	// {
		// return false;
	// }

	// if( NULL == opendir( pchDirPath ) )
	// {
		// return false;
	// }

	// return true;
    struct stat statbuf;
    if(lstat(pchDirPath, &statbuf) ==0)//lstat返回文件的信息，文件信息存放在stat结构中
    {
        return S_ISDIR(statbuf.st_mode) != 0;//S_ISDIR宏，判断文件类型是否为目录
    }

    return false;
}		/* -----  end of function IsDirExist  ----- */

//判断是否是特殊目录
bool IsSpecialDir(const char *pchDirPath)
{
    return strcmp(pchDirPath, ".") == 0 || strcmp(pchDirPath, "..") == 0;
}

//生成完整的文件路径
void GetTotalFilePath(const char *path, const char *file_name,  char *file_path)
{
    strcpy(file_path, path);
    if(file_path[strlen(path) - 1] != '/')
        strcat(file_path, "/");
    strcat(file_path, file_name);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ChangeFileMode
 *  Description:  修改文件权限
 *		  Param:  pszFileName:文件名
 *				  imode：权限在stat中宏定义
 *		 Return:
 * =====================================================================================
 */
bool ChangeFileMode ( char *pszFileName, int imode )
{
	if( NULL == pszFileName )
	{
		return false;
	}

	if( 0 == chmod ( pszFileName, imode ))
	{
		return true;
	}

	return false;
}		/* -----  end of function ChangeFileMode  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ChangedirFileMode
 *  Description:  修改文件权限 
 *		  Param:
 *		 Return:
 * =====================================================================================
 */
bool ChangedirFileMode ( char *pchDirPath ,int imode)
{
	DIR *dir;
	struct dirent *ptr;
	struct stat ;
	char base[1000];

	if ((dir=opendir(pchDirPath)) == NULL)
	{
		perror("Open dir error...");
		return false;

	}

	while ((ptr=readdir(dir)) != NULL)
	{
		if(IsSpecialDir( ptr->d_name ))    ///current dir OR parrent dir
			continue;
		else if(ptr->d_type == 8 ||     ///file
				ptr->d_type == 10)    ///link file
		{
			char chFileName[256];
			sprintf( chFileName, "%s/%s", pchDirPath, ptr->d_name );
			if(  !ChangeFileMode( chFileName, imode ) )	
			{
				closedir( dir );
				return false;
			}
		}
		else if(ptr->d_type == 4)    ///dir
		{
			memset(base,'\0',sizeof(base));
			strcpy(base,pchDirPath);
			strcat(base,"/");
			strcat(base,ptr->d_name);
			if( !ChangedirFileMode(base, imode))
			{
				closedir( dir );
				return false;
			}
		}
	}

	closedir(dir);
	return true ;
}		/* -----  end of function ChangedirFileMode  ----- */



void DeleteDirFiles(const char *path)
{
    DIR *dir = NULL;
    dirent *dir_info;
    char file_path[PATH_MAX];
    if(IsFileExist(path))
    {
        remove(path);
        return;
    }

    if(IsDirExist(path))
    {
        if((dir = opendir(path)) == NULL)
            return;
        while((dir_info = readdir(dir)) != NULL)
        {
            GetTotalFilePath(path, dir_info->d_name, file_path);
            if(IsSpecialDir(dir_info->d_name))
                continue;
            DeleteDirFiles(file_path);
            rmdir(file_path);
        }
    }

	closedir( dir );
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  MoveDirFiles
 *  Description:  移动文件或目录  利用rename进行实现
 *		  Param:
 *		 Return:
 * =====================================================================================
 */
bool MoveDirFiles ( char *pchSrcPath, char *pchDirPath )
{
	if( NULL == pchSrcPath
		|| NULL == pchDirPath )
	{
		return false;	
	}

	if( 0 == rename( pchSrcPath, pchDirPath ) )
	{
		return true;	
	}
	
	return false;
}		/* -----  end of function MoveDirFiles  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  测试使用 
 *		  Param:
 *		 Return:
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	GetDirSize( (char *)"../editor/" );
	printf ( "uiTotalSize=%u\n", uiTotalSize );

	printf ( "filesize=%lu\n", GetFileSize( (char *)"./main.cpp" ) );

	printf ( "direxist=%d\n", IsDirExist( (char *)"../fileoperation" ) );

	printf ( "fileexist=%d\n", IsFileExist( (char *)"./main.cpp" ) );

	MoveDirFiles( (char *)"./111/", (char *)"./222/" );
	MoveDirFiles( (char *)"./222/main.cpp", (char *)"./222/main.c" );
	if( ChangeFileMode( (char *)"/mynand/bin/gather", S_IRUSR | S_IRGRP ) )
	{
		printf ( "suc\n" );
	}
	else
	{
		printf ( "fail\n" );
	}

	ChangedirFileMode( (char *)"/mynand/bin/", S_IRUSR | S_IRGRP );

	// DeleteDirFiles( ( char * )"./222" );

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
