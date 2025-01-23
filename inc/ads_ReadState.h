#ifndef __ADS_READSTATE_H__
#define __ADS_READSTATE_H__

#include "ads_typdef.h"


/*
     ADS_ReadState
	 输入参数：(Ads_Handle_t *ctx ,AMS_ReadState_Receive_Dat_t *dat)
	 输出参数： 1成功， 0失败
*/
char ADS_ReadState(Ads_Handle_t *ctx ,AMS_ReadState_Receive_Dat_t *dat);

#endif