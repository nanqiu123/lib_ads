#ifndef _ADS_H_
#define _ADS_H_

#include "stdint.h"
#include "ads_typdef.h"


/*
     创建句柄 
	 输入参数：
	 输出参数：  句柄地址
*/
 Ads_Handle_t* ADS_CreatHandle(void);


 /*
     删除句柄 
	 输入参数：ctx: 句柄
	 输出参数：  
*/
void ADS_ReleaseHandle(Ads_Handle_t* ctx);


/*
     创建句柄  连接
	 输入参数： ctx:句柄	 ip: ip地址， port: 端口
	 输出参数： 1成功， 0失败 
*/
char ADS_Connect(Ads_Handle_t *ctx, uint8_t *ip, uint16_t port);




#endif 
