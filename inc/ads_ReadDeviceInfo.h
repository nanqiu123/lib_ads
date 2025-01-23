#ifndef __ADS_READDEVICE_H__
#define __ADS_READDEVICE_H__

#include "ads_typdef.h"

/*
     ADS_ReadDevice
	 输入参数： ctx: 句柄， gpoup_index： 区域， index_offset： 地址，AMS_ReadDevice_Receive_Dat_t *dat：数据
	 输出参数： 1成功， 0失败
*/
char ADS_ReadDevice(Ads_Handle_t *ctx ,ADS_GroupIndex_t gpoup_index, AMS_ReadDeviceInfo_Receive_Dat_t *dat);

#endif