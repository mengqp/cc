#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int const TITLE_LEN = 64;
static int const LINE_LEN = 1024;
#define GETINI_INT_ERROR  -1;
#define GETINI_HEX_ERROR  0xffffffff;

/*******************************************************************************
 * 函数名:GetIniKeyString
 * 功能描述:获取相应title下key所对应的值
 * 参数: char *title 配置文件中一组数据的标识
 * 参数: char *key 这组数据中要读出的值的标识
 * 参数: unsigned int len 读出值的最长长度
 * 参数: char *filename 要读取的文件路径
 * 返回值: 找到需要查的值则返回正确结果，否则返回NULL
 ******************************************************************************/
char * GetIniKeyString( char *title, char *key, char *buf, unsigned int len,  char *filename)
{
    FILE *fp;
    int flag = 0;
    char sTitle[TITLE_LEN], *tmp;
    char sLine[LINE_LEN];

    // 以只读方式打开文件
    fp = fopen(filename, "r");
    if ( NULL == fp )
    {
        perror("fopen");
        return NULL;
    }

    // 获取每行数据进行分析
    while ( NULL != fgets(sLine, LINE_LEN, fp ) )
    {
        // 开始是//或# 认为是注释
        if ( 0 == strncmp("//", sLine, 2)
             || '#' == sLine[0])
        {
            continue;
        }

        // 当找到title后 flag会置为1 查找key
        if ( 1 == flag )
        {
            // 如果有‘=’认为是有数据
            tmp = strchr( sLine, '=' );
            if ( NULL != tmp )
            {
                // 经较‘=’之前的字符串与key是否一致
                if ( 0 == strncmp(key, sLine, tmp - sLine ) )
                {
                    sLine[strlen(sLine)] = '\0';
                    fclose(fp);
                    if ( strlen(tmp) > ( len + 1) )
                    {
                        strncpy( buf, tmp+1, len);
                    }
                    else
                    {
                        strcpy( buf, tmp+1);
                    }

                    tmp = buf;
                    return tmp ;
                }
            }
        }
        else
        {
            sprintf( sTitle, "[%s]", title );
            if ( 0 == strncmp( sTitle, sLine, strlen(sLine) - 1 ) )
            {
                flag = 1;
            }
        }
    }

    fclose( fp );
    return NULL;
}   /*-------- end GetIniKeyString -------- */

/*******************************************************************************
 * 函数名:GetIniKeyInt
 * 功能描述:获取ini文件中title下key的数字值
 * 参数:char *title, char *key, char *filename
 * 参数:char *title, char *key, char *filename
 * 参数:char *title, char *key, char *filename
 * 参数:char *title, char *key, char *filename
 * 返回值:int
 ******************************************************************************/
int GetIniKeyInt(char *title, char *key, char *filename )
{
    char buf[LINE_LEN];
    int iRtn = GETINI_INT_ERROR;

    char *p = GetIniKeyString(title, key, buf, LINE_LEN, filename);
    if ( NULL != p)
    {
        sscanf( p, "%d", &iRtn );
    }
    return iRtn;
}   /*-------- end GetIniKeyInt -------- */

/*******************************************************************************
 * 函数名:GetIniKeyHex
 * 功能描述:获取ini文件中title下key的16进制值
 * 参数:char *title
 * 参数:char *key
 * 参数:char *filename
 * 返回值:int
 ******************************************************************************/
unsigned int GetIniKeyHex(char *title, char *key, char *filename)
{
    char buf[LINE_LEN];
    unsigned int uiRtn = GETINI_HEX_ERROR;
    char *p = GetIniKeyString(title, key, buf, LINE_LEN, filename);
    if ( NULL != p)
    {
        sscanf( p, "%x", &uiRtn );
    }
    return uiRtn;
}   /*-------- end GetIniKeyHex -------- */

/*******************************************************************************
 * 函数名:PutIniKeyString
 * 功能描述:设置ini文件中title下key的字符串值
 * 参数: char *title 配置文件中一组数据的标识
 * 参数: char *key 这组数据中要读出的值的标识
 * 参数: char *val 更改后的值
 * 参数: char *filename 要读取的文件路径
 * 返回值:bool 成功返回true 否则返回false
 ******************************************************************************/
bool PutIniKeyString( char *title, char *key, char *val, char *filename )
{
    FILE *fpr, *fpw;
    int flag = 0;
    char sLine[LINE_LEN], sTitle[TITLE_LEN], *tmp;

    // 以读的方式打开目标文件
    fpr = fopen( filename, "r");
    if ( NULL == fpr )
    {
        perror("fopen");
    }
    // 以写的方式创建临时文件
    sprintf(sLine, "%s.tmp", filename);
    fpw = fopen( sLine, "w" );
    if ( NULL == fpw )
    {
        perror("fopen");
    }

    // 读目标文件的每一行数据
    while ( NULL != fgets( sLine, LINE_LEN, fpr ) )
    {
        // 当flag 设定为2时为已找到目标值，不再需要改动
        if ( 2 != flag )
        {
            // 当flag 设定为1时为已找到修改值属于那一组数据
            if ( 1 == flag )
            {
                tmp = strchr( sLine, '=' );
                if ( NULL != tmp )
                {
                    // 当相等时为找到这组数据中值的标识
                    if ( 0 == strncmp(key, sLine, tmp - sLine ) )
                    {
                        // 设置flag为2
                        flag = 2;
                        // 组织一行数据
                        sprintf( tmp + 1, "%s\n", val );
                    }
                }
            }
            else
            {
                sprintf(sTitle, "[%s]", title );
                // 当相等时为找到标识组数据
                if ( 0 == strncmp(sTitle, sLine, strlen(sLine) - 1 ) )
                {
                    // 设置flag为1
                    flag = 1;
                }
            }
        }

        // 将每行数据写入临时文件
        fputs( sLine, fpw );
    }

    fclose( fpr );
    fclose( fpw );

    sprintf( sLine, "%s.tmp", filename );

    // 通过重命名的方式将临时文件更新为目标文件
    return rename( sLine, filename );
}   /*-------- end PutIniKeyString -------- */

/*******************************************************************************
 * 函数名:PutIniKeyInt
 * 功能描述:设置ini文件中title下key的int值
 * 参数: char *title 配置文件中一组数据的标识
 * 参数: char *key 这组数据中要读出的值的标识
 * 参数: char *val 更改后的值
 * 参数: char *filename 要读取的文件路径
 * 返回值:int
 ******************************************************************************/
int PutIniKeyInt( char *title, char *key, int val, char *filename )
{
    char sVal[32];
    sprintf(sVal, "%d", val);
    return PutIniKeyString(title, key, sVal, filename);
}   /*-------- end PutIniKeyInt -------- */

/*******************************************************************************
 * 函数名:PutIniKeyHex
 * 功能描述:设置ini文件中title下key的int值
 * 参数: char *title 配置文件中一组数据的标识
 * 参数: char *key 这组数据中要读出的值的标识
 * 参数: char *val 更改后的值
 * 参数: char *filename 要读取的文件路径
 * 返回值:int
 ******************************************************************************/
int PutIniKeyHex( char *title, char *key, unsigned int val, char *filename )
{
    char sVal[32];
    sprintf(sVal, "%x", val);
    return PutIniKeyString(title, key, sVal, filename);
}   /*-------- end PutIniKeyHex -------- */

int main(int argc,char *argv[])
{
    char buf[128] = "";
    /* int val; */
    printf("%s\n", GetIniKeyString((char *)"DOG", (char *)"name", buf, 1, (char *)"config.ini"));
    printf("%d\n", GetIniKeyInt((char *)"DOG", (char *)"age", (char *)"config.ini"));
    PutIniKeyString((char *)"CAT", (char *)"name", (char *)"ddd", (char *)"config.ini");
    PutIniKeyInt((char *)"DOG", (char *)"age", 28, (char *)"config.ini");
    return 0;
}
