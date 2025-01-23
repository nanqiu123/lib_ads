#ifndef __ADS_BASE_H__
#define __ADS_BASE_H__

#include "ads_typdef.h"
/*
     ADS_Header_BuildFrame
	 输入参数： AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header, 返回值：uint8_t *command_frame, uint16_t *command_lenth
	 输出参数： 1成功， 0失败
*/
char ADS_Header_BuildFrame(AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header, uint8_t *command_frame, uint16_t *command_lenth);


/*
     ADS_Header_ResolveFrame
	 输入参数：  uint8_t *command_frame, uint16_t command_lenth 返回值：AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header
	 输出参数： 1成功， 0失败
*/
char ADS_Header_ResolveFrame( uint8_t *command_frame, uint16_t command_lenth, AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header);

#endif


