#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <strings.h>

#include "ads_typedef.h"
#include "../inc/ads_log.h"

//==================================================================
//功能描述：ADS_Tcp_Connect
//输入参数：tcp_register
//返 回 值：1:success, 0:fail
//=================================================================
int8_t ADS_Tcp_Connect(Tcp_Register_t *tcp_register)
{
    struct sockaddr_in servaddr;
    int sockfd = 0;
   /*创建socket*/
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        return 0;
    }
    
    /*创建sockaddr_in结构体中相关参数*/
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(tcp_register->Tcp_Port);
    servaddr.sin_addr.s_addr= inet_addr((char *)tcp_register->Tcp_Ip);
    
    /*调用connect函数主动发起对服务端的链接*/
    if(connect(sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr))==-1)
    {
        return 0;
    }

    tcp_register->Socket_Handle = sockfd;
    
    return 1;
}


//==================================================================
//功能描述：tcp_is_connected
//输入参数：tcp_register
//返 回 值：1:connected, 0:disconnected
//==================================================================
int Ads_Tcp_Is_Connected(Tcp_Register_t *tcp_register)
{
    return tcp_register->Connect_State;
}


//==================================================================：
//功能描述：tcp Close 
//输入参数：tcp_register
//返 回 值：1:success, 0:fail
//=================================================================
int ADS_Tcp_Close(Tcp_Register_t *tcp_register)
{
    tcp_register->Connect_State = 0;
    return close(tcp_register->Socket_Handle);
}


//==================================================================
//功能描述：tcp_send
//输入参数：tcp_register  char *message, int lenth
//返 回 值：1:success, 0:fail
//==================================================================
int Ads_Tcp_Send(Tcp_Register_t *tcp_register, uint8_t *message, uint16_t lenth)
{
      if(Ads_Tcp_Is_Connected(tcp_register) != 1)
        return -1;

      return send(tcp_register->Socket_Handle ,message,lenth,0);
}


//==================================================================
//功能描述：tcp_receive
//输入参数：char *message, int *lenth
//返 回 值：1:success, 0:fail
//==================================================================
int Ads_Tcp_Receive(Tcp_Register_t *tcp_register,  uint8_t *message, uint16_t *lenth)
{
    if(Ads_Tcp_Is_Connected(tcp_register) != 1)
        return -1;

    int sta = recv(tcp_register->Socket_Handle,message, 65536,0);

    tcp_register->Connect_State = sta > 0? 1:0;
    if(sta < 0)  return 0;
    *lenth = sta;

    return 1;
}


