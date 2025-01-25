#ifndef _ADS_H_
#define _ADS_H_

#include "stdint.h"
#include "ads_typedef.h"


/*
     创建句柄 
	 输入参数：
	 输出参数：  句柄地址
*/
 Ads_Handle_t ADS_CreatHandle(void);


 /*
     删除句柄 
	 输入参数：ctx: 句柄
	 输出参数：  
*/
void ADS_ReleaseHandle(Ads_Handle_t ctx);


/*
     创建句柄  连接
	 输入参数： ctx:句柄	 ip: ip地址， port: 端口
	 输出参数： 1成功， 0失败 
*/
char ADS_Connect(Ads_Handle_t  ctx, uint8_t *ip, uint16_t port);


/*
     ADS协议 设置当前的IP 端口 
	 输入参数： ads ctx句柄； ams_netid_target ams_port_target: 目标ip、端口； ams_netid_source  ams_port_source：本机ip、端口；
	 输出参数： 1成功， 0失败
	 
*/
char ADS_SetVirtualIdPort(Ads_Handle_t  ctx ,uint8_t *ams_netid_target, uint16_t ams_port_target, uint8_t *ams_netid_source, uint16_t ams_port_source);


#endif 
