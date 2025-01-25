#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../inc/ads_inc.h"


#define ip "192.168.174.1"
#define port 48898


int main(int argc,char *argv[])
{
	Ads_Handle_t ads_client;

	ads_client = ADS_CreatHandle();
	if(0 == ADS_Connect(ads_client, ip, port))
	{
		printf("tcp connect fail!\r\n");
		exit(0);
	}
	printf("tcp connect success\r\n");


	ADS_SetVirtualIdPort(ads_client, "192.168.174.1.1.1", 801, "192.168.174.130.1.1", 48898);
	/*发送消息给服务端*/
	while(1)
	{
	   uint8_t sta = 0;
	//    AMS_ReadDeviceInfo_Receive_Dat_t ReadDeviceInfo_dat;
	//    ADS_ReadDeviceInfo(ads_client, &ReadDeviceInfo_dat);

	   printf("\r\nRead\r\n");
	   uint8_t Read_dat[100] = {0};
	   uint64_t Read_lenth = 0;
	   sta = ADS_Read(ads_client, ADS_GroupIndex_M, 1, 4, Read_dat, &Read_lenth);
	   if(sta)  printf("success\r\n");
	   else printf("fail\r\n");

	   printf("\r\nWrite\r\n");
	   uint8_t Write_dat[100] = {1};
	   sta = ADS_Write(ads_client, ADS_GroupIndex_MX, 100, Write_dat, 1);
	   if(sta)  printf("success\r\n");
	   else printf("fail\r\n");

	//    printf("\r\nRead State\r\n");
	//    AMS_ReadState_Receive_Dat_t ReadState_dat;
	//    sta = ADS_ReadState(ads_client, &ReadState_dat);
	//    if(sta)  printf("success\r\n");
	//    else printf("fail\r\n");
	   
	   printf("\r\nWrite Control\r\n");
	   uint8_t WriteControl_dat[100] = {0};
	   sta = ADS_WriteControl(ads_client,1,0, WriteControl_dat,10);
	   if(sta)  printf("success\r\n");
	   else printf("fail\r\n");

	   printf("\r\nAdd DeviceNotification\r\n");
	   AMS_AddDeviceNotification_Request_Dat_t AddDeciceNotification_dat;
	   uint8_t AddDeviceNotificationHandle[100] = {0};
	   sta = ADS_AddDeviceNotification(ads_client,&AddDeciceNotification_dat,AddDeviceNotificationHandle);
	   if(sta)  printf("success\r\n");
	   else printf("fail\r\n");

	   printf("\r\nDelete DeviceNotification\r\n");
	   uint32_t dELETEDeviceNotificationHandle= 0;;
	   sta = ADS_DeleteDeciveNitification(ads_client,dELETEDeviceNotificationHandle);
	   if(sta)  printf("success\r\n");
	   else printf("fail\r\n");

	   printf("\r\nread write\r\n");
	   Ads_ReadWrite_Dat_t ReadWrite_dat;
	   uint8_t ReadWrite_FeedbackDate[100] = {0};
	   uint64_t *ReadWrite_Feedback_lenth;

	   ReadWrite_dat.Index_Group = ADS_GroupIndex_HANDLE;
	   ReadWrite_dat.Index_Offset = 0;
	   ReadWrite_dat.Read_Lenth = 4;
	   ReadWrite_dat.Data = "name";
	   ReadWrite_dat.Write_Lenth = strlen(ReadWrite_dat.Data);
	   sta = ADS_ReadWrite(ads_client,&ReadWrite_dat, ReadWrite_FeedbackDate, &ReadWrite_Feedback_lenth);
	   if(sta)  printf("success\r\n");
	   else printf("fail\r\n");

	   exit(0);
	}

}
