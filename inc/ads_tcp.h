#ifndef _ADS_TCP_H_
#define _ADS_TCP_H_
#include <stdint.h>

//==================================================================
//函 数 名：
//功能描述：tcp connect 
//输入参数：ip,port
//返 回 值：1:success, other:fail
//=================================================================
int ADS_Tcp_Connect(uint8_t *ip, uint16_t port);

//==================================================================
//函 数 名：
//功能描述：tcp_is_connected
//输入参数：char *ip, unsigned int port, char *message, int *lenth
//返 回 值：1:connected, other:disconnected
//==================================================================
int Ads_Tcp_Is_Connected();

//==================================================================
//函 数 名：
//功能描述：tcp Close 
//输入参数：
//返 回 值：1:success, other:fail
//=================================================================
int ADS_Tcp_Close();

//==================================================================
//函 数 名：
//功能描述：tcp_send
//输入参数：char *message, int lenth
//返 回 值：1:success, other:fail
//==================================================================
int Ads_Tcp_Send(uint8_t *message, uint16_t lenth);

//==================================================================
//函 数 名：
//功能描述：tcp_receive
//输入参数：char *message, int *lenth
//返 回 值：1:success, other:fail
//==================================================================
int Ads_Tcp_Receive(uint8_t *message, uint16_t *lenth);

#endif 