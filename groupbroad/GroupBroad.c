/*++
***************************************************************************************************

(c) 版权所有: 

模块名称:

	GroupBroad.c

摘要:

	建立内部总线的基本格式及传送

作者:

	mengqp--- 2014-04-30

修改历史:
	x、what---who---time

***************************************************************************************************  
--*/


#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include   <sys/types.h> 
#include   <sys/socket.h> 
#include   <netinet/in.h> 
#include   <arpa/inet.h> 
#include <stdio.h>
#include <string.h>


#define MCAST_PORT 65529
#define MCAST_ADDR "224.0.0.100"    /*一个局部连接多播地址，路由器不进行转发*/
#define BUFF_SIZE 1024


static int rcv_fd = -1;
static int sd_fd = -1;
static struct sockaddr_in r_addr;
static struct sockaddr_in local_addr;				/*本地地址*/


#define	LOCAL_DATA_MAXLEN 1024			/*  */

unsigned short GroupBroadRecv(unsigned char* pBuf,int* pLen)
{
	

	socklen_t len = sizeof(local_addr);

	if(rcv_fd<=0)
	{
		return -1;
	}


 	* pLen = recvfrom (rcv_fd, pBuf, 1024, 0,(struct sockaddr *) &local_addr,&len);

 	if (* pLen < 0 )
    {
		perror ("recvfrom");
        return (-1);
    }
    else
    {

    }
    //inet_ntoa_b (clientAddr.sin_addr, inetAddr);
 
 	return 0;	
}


static int GroupBroadSendEn(unsigned char* pBuf,int Len)
{

	if(sd_fd<=0)
	{
		return -1;
	}
	if(Len>LOCAL_DATA_MAXLEN) 
	{
		Len=LOCAL_DATA_MAXLEN;
		//printf("\n[MlGroupBroadSend]data overflow...");
	}

	
	if (sendto (sd_fd, pBuf, Len, 0, (struct sockaddr *)&r_addr, sizeof (r_addr)) < 0 )
	{

		return (-1);
	}
	else
	{
		return (1);
	}
}

static int MutexInited = 0;
static pthread_mutex_t  mutex;

int GroupBroadSend(unsigned char* pBuf,int Len)
{
	if(MutexInited == 0)
	{
		pthread_mutex_init (&mutex, NULL);
		MutexInited=1;
	}
	pthread_mutex_lock(&mutex);
	GroupBroadSendEn(pBuf, Len);
	pthread_mutex_unlock(&mutex);
	return 0;
}

static int GroupBroadSendInit(void)
{
    //int s;
    //struct sockaddr_in r_addr;     
    sd_fd = socket(AF_INET, SOCK_DGRAM, 0);         /*建立套接字*/
    if (sd_fd== -1)
    {
        perror("socket()");
        return -1;
    }
   
    memset(&r_addr, 0, sizeof(r_addr));/*初始化IP多播地址为0*/
    r_addr.sin_family = AF_INET;                /*设置协议族类行为AF*/
    r_addr.sin_addr.s_addr = inet_addr(MCAST_ADDR);/*设置多播IP地址*/
    r_addr.sin_port = htons(MCAST_PORT);        /*设置多播端口*/
   
                                                    /*向多播地址发送数据*/
   
    return 0;
}


static int GroupBroadRecvInit(void)
{                                      
    int err = -1;
    rcv_fd = socket(AF_INET, SOCK_DGRAM, 0);     /*建立套接字*/

    if (sd_fd == -1)
    {
        perror("socket()");
        return -1;
    }  
   
                                                /*初始化地址*/
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(MCAST_PORT);
   
	int  reuseaddr= 1;
	err = setsockopt(rcv_fd,IPPROTO_IP, SO_REUSEADDR,&reuseaddr, sizeof(reuseaddr));
	if(err < 0)
	{
		perror("setsockopt():IP_MULTICAST_LOOP");
		return -3;
	}
                                                /*绑定socket*/
    err = bind(rcv_fd,(struct sockaddr*)&local_addr, sizeof(local_addr)) ;
    if(err < 0)
    {
        perror("bind()");
        return -2;
    }
   
                                                /*设置回环许可*/
    /* int loop = 0; */
    /* err = setsockopt(rcv_fd,IPPROTO_IP, IP_MULTICAST_LOOP,&loop, sizeof(loop)); */
    /* if(err < 0) */
    /* { */
        /* perror("setsockopt():IP_MULTICAST_LOOP"); */
        /* return -3; */
    /* } */
   
    struct ip_mreq mreq;                                    /*加入多播组*/
    mreq.imr_multiaddr.s_addr = inet_addr(MCAST_ADDR); /*多播地址*/
    mreq.imr_interface.s_addr = htonl(INADDR_ANY); /*网络接口为默认*/
                                                        /*将本机加入多播组*/
    err = setsockopt(rcv_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,&mreq, sizeof
    (mreq));
    if (err < 0)
    {
        perror("setsockopt():IP_ADD_MEMBERSHIP");
        return -4;
    }
  


    return 0;
}

int GroupBroadInit(void)
{
	if( sd_fd > 0 )
	{
		shutdown( sd_fd, 2 );
		close( sd_fd );
		sd_fd = -1;
	}
	if( rcv_fd > 0 )
	{
		shutdown( rcv_fd, 2 );
		close( rcv_fd );
		rcv_fd = -1;
	}
	

	if( 0 >  GroupBroadSendInit() )
	{
		printf ( "GroupBroadSendInit error\n" );
		return -1;
	}

	if ( 0 >  GroupBroadRecvInit(  ) )
	{
		printf ( "GroupBroadRecvInit error\n" );
		return -1;
	}

	return 0;
}


