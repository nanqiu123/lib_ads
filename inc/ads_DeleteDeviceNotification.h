#ifndef __ADS_deleteDECIVENOTIFICATION_H__
#define __ADS_DeleteDECIVENOTIFICATION_H__

#include "ads_typedef.h"

/*
     ADS_DeleteDeciveNitification
	 输入参数： (Ads_Handle_t  ctx , uint8_t *handle_of_notification)
	 输出参数： 1成功， 0失败
*/
char ADS_DeleteDeciveNitification(Ads_Handle_t  ctx , uint8_t handle_of_notification);

#endif