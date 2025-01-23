#ifndef _ADS_TCP_H_
#define _ADS_TCP_H_
#include <stdint.h>
#include "ads_typdef.h"

//==================================================================
//功能描述：ADS_Tcp_Connect
//输入参数：tcp_register
//返 回 值：1:success, 0:fail
//=================================================================
int8_t ADS_Tcp_Connect(Tcp_Register_t *tcp_register);

//==================================================================
//功能描述：tcp_is_connected
//输入参数：tcp_register
//返 回 值：1:connected, 0:disconnected
//==================================================================
int Ads_Tcp_Is_Connected(Tcp_Register_t *tcp_register);

//==================================================================：
//功能描述：tcp Close 
//输入参数：tcp_register
//返 回 值：1:success, 0:fail
//=================================================================
int ADS_Tcp_Close(Tcp_Register_t *tcp_register);

//==================================================================
//功能描述：tcp_send
//输入参数：tcp_register  char *message, int lenth
//返 回 值：1:success, 0:fail
//==================================================================
int Ads_Tcp_Send(Tcp_Register_t *tcp_register, uint8_t *message, uint16_t lenth);

//==================================================================
//功能描述：tcp_receive
//输入参数：char *message, int *lenth
//返 回 值：1:success, 0:fail
//==================================================================
int Ads_Tcp_Receive(Tcp_Register_t *tcp_register,  uint8_t *message, uint16_t *lenth);

#endif 