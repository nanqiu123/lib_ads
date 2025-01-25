#ifndef __ADS_DECIVENOTIFICATION_H__
#define __ADS_DECIVENOTIFICATION_H__

#include "ads_typedef.h"

/*
     ADS_DeviceNitification  因资料不够，无法实现
	 输入参数： (Ads_Handle_t  ctx , uint8_t *handle_of_notification)
	 输出参数： 1成功， 0失败
*/
char ADS_DeviceNitification(Ads_Handle_t  ctx , AMS_DeviceNotification_Request_Dat_t *dat);

#endif