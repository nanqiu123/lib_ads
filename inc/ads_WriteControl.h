#ifndef __ADS_WRITECONTROL_H__
#define __ADS_WRITECONTROL_H__

#include "ads_typedef.h"



/*
    ADS_WriteControl
	 输入参数： ctx: 句柄，  dat：数据
*/
char ADS_WriteControl(Ads_Handle_t  ctx, uint16_t ads_state, uint16_t device_sate, uint8_t *dat, uint16_t lenth);

#endif