#ifndef __ADS_READ_H__
#define __ADS_READ_H__

#include "ads_typedef.h"

/*
     ADS_Read
	 输入参数： ctx:句柄； gpoup_index：读区域； index_offset：读地址； read_lenth：读字节数；feedback_dat：返回数据； feedback_lenth：返回数据长度；
	 输出参数： 1成功， 0失败
*/
char ADS_Read(Ads_Handle_t ctx ,ADS_GroupIndex_t gpoup_index, uint64_t index_offset, uint8_t read_lenth, uint8_t *feedback_dat, uint64_t *feedback_lenth);

#endif