#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../inc/ads_tcp.h"
#include "../inc/ads.h"
#include "log.h"

 #define ip "192.168.174.1"
 #define port 48898

// #define ip "192.168.10.1"
// #define port 48898

int main(int argc,char *argv[])
{
    char buf[200] = {0};
	int len = 0, sta = 0;

	/*调用connect函数主动发起对服务端的链接*/
	if(!ADS_Tcp_Connect(ip, port))
	{
		LOG_RPINTF("disconnect");
		exit(-1);
	}
	sleep(1);
	
	
    ADS_SetIdPort("192.168.163.8.1.1:851", "192.168.174.130.1.1:48898");
	//ADS_SetIdPort("172.18.236.114.1.1:801", "192.168.10.230.1.1:0");

	/*发送消息给服务端*/
	while(1)
	{
		LOG_RPINTF("start");
		if(Ads_Tcp_Is_Connected()!= 1)
		{
			LOG_RPINTF("disconnect");
		}

		uint8_t response[100] = {0};
		uint16_t response_lenth = 0;
		uint8_t writting[10] = {0};

		ADS_ReadWrite_Read("BaseModule.Mco.Conveyor_VelocitySoftMode",4,response, &response_lenth);
		ADS_ReadWrite_Read("BaseModule.Act.CycleTime_L2",4,response, &response_lenth);

	}
}

