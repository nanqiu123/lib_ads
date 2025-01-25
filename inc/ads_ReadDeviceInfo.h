#ifndef __ADS_READDEVICE_H__
#define __ADS_READDEVICE_H__

#include "ads_typedef.h"

/*
     ADS_ReadDeviceInfo
	 输入参数： ctx: 句柄,AMS_ReadDeviceInfo_Receive_Dat_t *dat：数据
	 输出参数： 1成功， 0失败
*/
char ADS_ReadDeviceInfo(Ads_Handle_t  ctx, AMS_ReadDeviceInfo_Receive_Dat_t *dat);

#endif