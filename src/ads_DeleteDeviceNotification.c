#include <stdlib.h>
#include <string.h>
#include "../inc/ads_DeleteDeviceNotification.h"
#include "../inc/ads_tcp.h"
#include "../inc/ads_tools.h"
#include "../inc/ads_base.h"
#include "../inc/log.h"
/*
     组帧
	 输入参数： (ADS_DeleteDeviceNotification_Request_t *command, uint8_t *command_frame, uint16_t *command_lenth)
	 输出参数： 1成功， 0失败
*/
static char ADS_DeleteDeciveNitification_BuildFrame(ADS_DeleteDeviceNotification_Request_t *command, uint8_t *command_frame, uint16_t *command_lenth)
{
   uint16_t index = 0;
   if(command == NULL || command_frame == NULL) return 0;
   if(0 == ADS_Header_BuildFrame(&command->Ams_Tcp_Header, &command->Ams_Header, command_frame, &index)) return  0;

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Notification_Handle, sizeof(command->Request.Notification_Handle), &command_frame[index]);
   index += sizeof(command->Request.Notification_Handle);

   *command_lenth = index;
   return 1;
}


/*
     DeleteDeviceNotification 解析帧
	 输入参数： (uint8_t *command_frame, uint16_t command_lenth, ADS_DeleteDeviceNotification_Receive_t *command)
	 输出参数： 1成功， 0失败
*/
char ADS_DeleteDeciveNitification_ResolevFrame(uint8_t *command_frame, uint16_t command_lenth, ADS_DeleteDeviceNotification_Receive_t *command)
{
   uint16_t index = 0;
   if(command == NULL || command_frame == NULL) return 0;

   if(command_lenth <= AMS_HEADER_BYTES) return 0;
   if(command_frame[0] != 0 || command_frame[1] != 0) return 0;

   if(0 == ADS_Header_ResolveFrame(command_frame, command_lenth, &command->Ams_Tcp_Header, &command->Ams_Header)) return 0;  

   index += AMS_HEADER_BYTES;

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&command->Receive.Result, sizeof(command->Receive.Result));
   index += sizeof(command->Receive.Result);
   
   return 1;
}


/*
     ADS_DeleteDeciveNitification
	 输入参数： (Ads_Handle_t *ctx , uint8_t *handle_of_notification)
	 输出参数： 1成功， 0失败
*/
char ADS_DeleteDeciveNitification(Ads_Handle_t *ctx , uint8_t handle_of_notification)
{
    ADS_DeleteDeviceNotification_Request_t command_send;
	 ADS_DeleteDeviceNotification_Receive_t command_receive;
	
	 uint8_t send_buff[1024] = {0};
	 uint16_t send_lenth = 0;
	 
    uint8_t receive_buff[1024] = {0};
	 uint16_t receive_lenth = 0;


	 if(ctx == NULL) return 0;
	
	 command_send.Ams_Tcp_Header.Reserved = 0;
	 command_send.Ams_Tcp_Header.Command_Lenth = (uint32_t)(AMS_HEADER_BYTES + AMS_DELETEEVICENOTIFICATION_REQUEST_DAT_BASE_BYTES);

	 memcpy(command_send.Ams_Header.AMSNetId_Target,  ctx->Ads_Register.AMSNetId_Target, sizeof(ctx->Ads_Register.AMSNetId_Target));
	 command_send.Ams_Header.AMSPort_Target = ctx->Ads_Register.AMSPort_Target;
	
	 memcpy(command_send.Ams_Header.AMSNetId_Source,  ctx->Ads_Register.AMSNetId_Source, sizeof(ctx->Ads_Register.AMSNetId_Source));
	 command_send.Ams_Header.AMSPort_Source = ctx->Ads_Register.AMSPort_Source;
	
	 command_send.Ams_Header.Command_Id = (uint16_t)ADS_CmdId_DeleteDeviceNotification;
	 
	 command_send.Ams_Header.State_Flags = (uint16_t)ADS_StateFlags_COMMAND;
	
	 command_send.Ams_Header.Data_Length = AMS_DELETEEVICENOTIFICATION_REQUEST_DAT_BASE_BYTES;     // 数据域长度
	
	 command_send.Ams_Header.Error_Code = (uint32_t)ADS_ErrorCode_NoError;
	 
	 command_send.Ams_Header.Invoke_Id = 1;       // 写多少都行


    command_send.Request.Notification_Handle = handle_of_notification;
    
	 if(0 == ADS_DeleteDeciveNitification_BuildFrame(&command_send, send_buff, &send_lenth)) return 0;  
	 	 
	 LOG_RPINTF("send lenth: %d\n", send_lenth);
	 printf_array("send buff: ", send_buff, send_lenth);
	 if(0 == Ads_Tcp_Send(&ctx->Tcp_Register, send_buff, send_lenth)) return 0;

	 
	 if(0 == Ads_Tcp_Receive(&ctx->Tcp_Register, receive_buff, &receive_lenth)) return 0;
	 LOG_RPINTF("DeleteDeviceNotification lenth: %d\n", receive_lenth);
	 printf_array("DeleteDeviceNotification buff: ", receive_buff, receive_lenth);

	 if(0 == ADS_DeleteDeciveNitification_ResolevFrame(receive_buff, receive_lenth, &command_receive)) return 0;

    if(command_receive.Ams_Header.Error_Code != ADS_ErrorCode_NoError) return 0;
    if(command_receive.Receive.Result != ADS_ErrorCode_NoError) return 0;

	 return 1;
}