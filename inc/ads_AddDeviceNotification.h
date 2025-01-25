#ifndef __ADS_ADDDEVICENOTIFICATION_H__
#define __ADS_ADDDEVICENOTIFICATION_H__

#include "ads_typedef.h"

/*
     ADS_AddDeviceNotification
	 输入参数： (Ads_Handle_t  ctx , AMS_AddDeviceNotification_Request_Dat_t *dat, uint8_t *handle_of_notification)
	 输出参数： 1成功， 0失败
*/
char ADS_AddDeviceNotification(Ads_Handle_t ctx , AMS_AddDeviceNotification_Request_Dat_t *dat, uint8_t *handle_of_notification);

#endif