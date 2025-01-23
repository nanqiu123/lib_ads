#ifndef __ADS_ReadWrite_H__
#define __ADS_ReadWrite_H__

#include "ads_typdef.h"


/*
     ADS_ReadWrite
	 输入参数： (Ads_Handle_t *ctx ,Ads_ReadWrite_Dat_t *dat, uint8_t *return_date, uint64_t *lenth)
	 输出参数： 1成功， 0失败
*/
char ADS_ReadWrite(Ads_Handle_t *ctx ,Ads_ReadWrite_Dat_t *dat, uint8_t *return_date, uint64_t *lenth);

#endif