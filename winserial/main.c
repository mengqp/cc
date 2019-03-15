#include    "com.h"
#include	<stdlib.h>

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    int iRtn = 0xff;
    unsigned int port = 4;
    int maxLen = 1024;
    unsigned char buf[maxLen];

    if( argc  >=  2 )
    {
        port = (unsigned int)atoi( argv[1] );
    }

    iRtn = OpenComPort( port, 9600);
    if( 0 == iRtn )
    {
        printf ( "can't open the port com%d\n", port );
        return -1;
    }

    while ( 1 )
    {
        int ReadLen = ReadComBuf( buf,  maxLen );
        if( ReadLen > 0 )
        {
            int i;
            for( i=0; i<ReadLen; i++ )
            {
                printf ( "%x ", buf[i] );
            }
            printf ( "\n" );

            WriteComBuf( buf,  ReadLen);
            printf ( "write\n" );
        }
    }


    CloseComPort( );
    printf ( "hello world\n" );
    return 0;
}				/* ----------  end of function main  ---------- */
