/*******************************************************************************
 * 文件名:main.c
 * 文件描述:判断系统的大小端
 * 作者:mengqp
 * 创建日期:2017/01/11 09:06:56
 * 公司：
 * 版本：Ver1.0
 *
 * 历史版本：
 * 修改人                修改时间                修改版本        修改内容
 *
 *
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*******************************************************************************
 * 函数名:testsize
 * 功能描述:
 * 参数: char *buf
 * 返回值:void
 ******************************************************************************/
void testsize( char buf[] )
{
    printf("tmp=%d\n", sizeof(buf) );
}   /*-------- end testsize -------- */

/*******************************************************************************
 * 函数名:test
 * 功能描述:
 * 参数:void
 * 返回值:void
 ******************************************************************************/
/*******************************************************************************
 * 函数名:IsBigEndian
 * 功能描述:判断大小端，大端返回true 小端返加false
 * 参数:void
 * 返回值:bool
 ******************************************************************************/
bool IsBigEndian(void)
{
    int i=1;

    char *p=(char *)&i;

    if ( 1 == *p)
    {
        return false;
    }
    else
    {
        return true;
    }

    return true;
}   /*-------- end IsBigEndian -------- */

/*******************************************************************************
 * 函数名:GlobalCopyByEndian
 * 功能描述:根据大小端模式拷贝buf
 * 参数: char *dest 目标buf
 * 参数: char *src 源buf
 * 参数: int num 要拷贝的数量
 * 返回值:bool
 ******************************************************************************/
bool GlobalCopyByEndian( unsigned char *dest, unsigned char *src, unsigned int num )
{
    if ( NULL == dest || NULL == src )
    {
        return false;
    }

    // 不拷虑dest和src内存重合
    if ( !IsBigEndian( ) )
    {
        src += num-1;
        while( 0 != num-- )
        {
            *( dest++ ) = *( src-- );
        }
    }
    else
    {
        while( 0 != num-- )
        {
            *( dest++ ) = *( src++ );
        }
    }

    return true;
}   /*-------- end GlobalCopyByEndian -------- */

void test(void)
{
    float f = 232.11;
    char buf[4] = "", tmp[5] = "";

    memcpy( buf, &f, 4);

    /* tmp[0] = buf[3]; */
    /* tmp[1] = buf[2]; */
    /* tmp[2] = buf[1]; */
    /* tmp[3] = buf[0]; */

    /* testsize(tmp); */
    GlobalCopyByEndian( (unsigned char *)tmp, (unsigned char *)buf, 4);

    printf("f=%.8x buf=%.8x tmp=%.8x\n",
           ( int ) f,
           ( int )buf,
           ( int )tmp);
    printf("buf=%x %x %x %x\n", buf[0], buf[1], buf[2], buf[3]);
    printf("tmp=%x %x %x %x\n", tmp[0], tmp[1], tmp[2], tmp[3]);
}   /*-------- end test -------- */


int main(int argc, char *argv[])
{
    int i=1;

    char *p=(char *)&i;

    if(*p==1)
        printf("Little_endian\n");   //Little_endian
    else
        printf("Big_endian\n");   //Big_endian

    test();
    return 0;
}
