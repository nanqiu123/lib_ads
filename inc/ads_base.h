#ifndef __ADS_BASE_H__
#define __ADS_BASE_H__

#include "ads_typedef.h"
/*
     ADS_Header_BuildFrame
	 输入参数： AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header, 返回值：uint8_t *command_frame, uint16_t *command_lenth
	 输出参数： 1成功， 0失败
*/
char ADS_Header_BuildFrame(AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header, uint8_t *command_frame, uint16_t *command_lenth);


/*
     ADS_Header_ResolveFrame
	 输入参数：  ( uint8_t *command_frame, AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header)
	 输出参数： 1成功， 0失败
*/
char ADS_Header_ResolveFrame( uint8_t *command_frame, AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header);


/*
    打印AMS_TCP_Header_t和AMS_Header_t
	 输入参数： AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header
	 输出参数： 1成功， 0失败
*/
char ADS_Header_Printf(AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header);
#endif


