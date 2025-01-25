#ifndef __ADS_WRITE_H__
#define __ADS_WRITE_H__

#include "ads_typedef.h"


/*
     ADS_Write
	 输入参数： ctx: 句柄， gpoup_index： 区域， index_offset： 地址， dat：数据， lenth 数据长度
	 输出参数： 1成功， 0失败
*/
char ADS_Write(Ads_Handle_t  ctx ,ADS_GroupIndex_t gpoup_index, uint64_t index_offset, uint8_t *dat, uint64_t lenth);

#endif