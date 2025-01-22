#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <poll.h>
#include "log.h"
int sockfd = 0;
int socket_statue = 0;

//==================================================================
//函 数 名：
//功能描述：tcp connect 
//输入参数：ip,port
//返 回 值：1:success, other:fail
//=================================================================
int ADS_Tcp_Connect(uint8_t *ip, uint16_t port)
{
    struct sockaddr_in servaddr;
   /*创建socket*/
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
         LOG_RPINTF("socket build error\r\n");
        return -1;
    }
    else
    {
        LOG_RPINTF("socket build success\r\n");
    }
    
    /*创建sockaddr_in结构体中相关参数*/
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    servaddr.sin_addr.s_addr= inet_addr((char *)ip);
    
    /*调用connect函数主动发起对服务端的链接*/
    if(connect(sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr))==-1)
    {
        return -1;
    }

    socket_statue = 1;
    return 1;
}

//==================================================================
//函 数 名：
//功能描述：tcp_is_connected
//输入参数：char *ip, unsigned int port, char *message, int *lenth
//返 回 值：1:connected, other:disconnected
//==================================================================
int Ads_Tcp_Is_Connected()
{
    return socket_statue;
}


//==================================================================
//函 数 名：
//功能描述：tcp Close 
//输入参数：
//返 回 值：1:success, other:fail
//=================================================================
int ADS_Tcp_Close()
{
    socket_statue = 0;
    return close(sockfd);
}



//==================================================================
//函 数 名：
//功能描述：tcp_send
//输入参数：char *message, int lenth
//返 回 值：1:success, other:fail
//==================================================================
int Ads_Tcp_Send(uint8_t *message, uint16_t lenth)
{
      if(Ads_Tcp_Is_Connected() != 1)
        return -1;

      return send(sockfd,message,lenth,0);
}


//==================================================================
//函 数 名：
//功能描述：tcp_receive
//输入参数：char *message, int *lenth
//返 回 值：1:success, other:fail
//==================================================================
int Ads_Tcp_Receive(uint8_t *message, uint16_t *lenth)
{
    if(Ads_Tcp_Is_Connected() != 1)
        return -1;

    int sta = recv(sockfd,message, 200,0);

    socket_statue = sta > 0? 1:-1;
    if(sta < 0)  return 0;
    *lenth = sta;
    return 1;
}


