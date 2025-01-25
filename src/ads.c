#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/ads.h"
#include "../inc/ads_tcp.h"
#include "../inc/ads_tools.h"
#include "../inc/ads_log.h"
#include "../inc/ads_tools.h"

/*
     创建句柄 
	 输入参数：
	 输出参数：  句柄地址
*/
 Ads_Handle_t ADS_CreatHandle(void)
{
	return (Ads_Handle_t)malloc(sizeof(Ads_Handle_));
}


/*
     删除句柄 
	 输入参数：ctx: 句柄
	 输出参数：  
*/
void ADS_ReleaseHandle(Ads_Handle_t ctx)
{
	free(ctx);
}


/*
     创建句柄  连接
	 输入参数： ctx:句柄	 ip: ip地址， port: 端口
	 输出参数： 1成功， 0失败 
*/
char ADS_Connect(Ads_Handle_t  ctx, uint8_t *ip, uint16_t port)
{
	ctx->Tcp_Register.Tcp_Port = port;
	strcpy((char *)ctx->Tcp_Register.Tcp_Ip, (char *)ip);

	ctx->Tcp_Register.Connect_State = ADS_Tcp_Connect(&ctx->Tcp_Register);

	return ctx->Tcp_Register.Connect_State;
}


/*
     ADS协议 设置当前的IP 端口 
	 输入参数： ads ctx句柄； ams_netid_target ams_port_target: 目标ip、端口； ams_netid_source  ams_port_source：本机ip、端口；
	 输出参数： 1成功， 0失败
	 
*/
char ADS_SetVirtualIdPort(Ads_Handle_t ctx ,uint8_t *ams_netid_target, uint16_t ams_port_target, uint8_t *ams_netid_source, uint16_t ams_port_source)
{
     if(ams_netid_target == NULL || ams_netid_source == NULL) return 0;
	
	  sscanf(ams_netid_target, "%hhd.%hhd.%hhd.%hhd.%hhd.%hhd", 
	  &ctx->Ads_Register.AMSNetId_Target[0],
	  &ctx->Ads_Register.AMSNetId_Target[1],
	  &ctx->Ads_Register.AMSNetId_Target[2],
	  &ctx->Ads_Register.AMSNetId_Target[3],
	  &ctx->Ads_Register.AMSNetId_Target[4],
	  &ctx->Ads_Register.AMSNetId_Target[5]
	  );

      ctx->Ads_Register.AMSPort_Target = ams_port_target; 

	  sscanf(ams_netid_source, "%hhd.%hhd.%hhd.%hhd.%hhd.%hhd", 
	  &ctx->Ads_Register.AMSNetId_Source[0],
	  &ctx->Ads_Register.AMSNetId_Source[1],
	  &ctx->Ads_Register.AMSNetId_Source[2],
	  &ctx->Ads_Register.AMSNetId_Source[3],
	  &ctx->Ads_Register.AMSNetId_Source[4],
	  &ctx->Ads_Register.AMSNetId_Source[5]
	  );

      ctx->Ads_Register.AMSPort_Source = ams_port_source; 
	 
	 return 1;
}




