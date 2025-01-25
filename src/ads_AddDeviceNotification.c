#include <stdlib.h>
#include <string.h>
#include "../inc/ads_AddDeviceNotification.h"
#include "../inc/ads_tcp.h"
#include "../inc/ads_tools.h"
#include "../inc/ads_base.h"
#include "../inc/ads_log.h"

/*
     组帧  
	 输入参数： (ADS_AddDeviceNotification_Request_t *command, uint8_t *command_frame, uint16_t *command_lenth)
	 输出参数： 1成功， 0失败
*/
static char ADS_AddDeciveNitification_BuildFrame(ADS_AddDeviceNotification_Request_t *command, uint8_t *command_frame, uint16_t *command_lenth)
{
   uint16_t index = 0;
   if(command == NULL || command_frame == NULL) return 0;
   if(0 == ADS_Header_BuildFrame(&command->Ams_Tcp_Header, &command->Ams_Header, command_frame, &index)) return  0;

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Index_Group, sizeof(command->Request.Index_Group), &command_frame[index]);
   index += sizeof(command->Request.Index_Group);

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Index_Offset, sizeof(command->Request.Index_Offset), &command_frame[index]);
   index += sizeof(command->Request.Index_Offset);

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Lenth, sizeof(command->Request.Lenth), &command_frame[index]);
   index += sizeof(command->Request.Lenth);

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Transmission_Mode, sizeof(command->Request.Transmission_Mode), &command_frame[index]);
   index += sizeof(command->Request.Transmission_Mode);

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Max_Delay, sizeof(command->Request.Max_Delay), &command_frame[index]);
   index += sizeof(command->Request.Max_Delay);

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Cycle_Time, sizeof(command->Request.Cycle_Time), &command_frame[index]);
   index += sizeof(command->Request.Cycle_Time);

  
   memset(&command_frame[index], 0,  sizeof(command->Request.Reserved));
   index += sizeof(command->Request.Reserved);

   *command_lenth = index;
   return 1;
}


/*
     AddDeviceNotification 解析帧
	 输入参数： (uint8_t *command_frame, uint16_t command_lenth, ADS_AddDeviceNotification_Receive_t *command)
	 输出参数： 1成功， 0失败
*/
char ADS_AddDeciveNitification_ResolevFrame(uint8_t *command_frame, uint16_t command_lenth, ADS_AddDeviceNotification_Receive_t *command)
{
   uint16_t index = 0;
   if(command == NULL || command_frame == NULL) return 0;

   if(command_lenth <= AMS_HEADER_BYTES) return 0;
   if(command_frame[0] != 0 || command_frame[1] != 0) return 0;

   if(0 == ADS_Header_ResolveFrame(command_frame, &command->Ams_Tcp_Header, &command->Ams_Header)) return 0;  

   index += AMS_HEADER_BYTES + AMS_TCP_HEADER_BYTES;

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&command->Receive.Result, sizeof(command->Receive.Result));
   index += sizeof(command->Receive.Result);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index],  (uint64_t *)&command->Receive.Notification_Handle, sizeof(command->Receive.Notification_Handle));
   index += sizeof(command->Receive.Notification_Handle);
   
   return 1;
}


/*
     ADS_AddDeviceNotification
	 输入参数： (Ads_Handle_t *ctx , AMS_AddDeviceNotification_Request_Dat_t *dat, uint8_t *handle_of_notification)
	 输出参数： 1成功， 0失败
*/
char ADS_AddDeviceNotification(Ads_Handle_t ctx , AMS_AddDeviceNotification_Request_Dat_t *dat, uint8_t *handle_of_notification)
{
    ADS_AddDeviceNotification_Request_t command_send;
	 ADS_AddDeviceNotification_Receive_t command_receive;
	
	 uint8_t send_buff[1024] = {0};
	 uint16_t send_lenth = 0;
	 
    uint8_t receive_buff[1024] = {0};
	 uint16_t receive_lenth = 0;


	 if(ctx == NULL || dat == NULL) return 0;
	
	 command_send.Ams_Tcp_Header.Reserved = 0;
	 command_send.Ams_Tcp_Header.Command_Lenth = (uint32_t)(AMS_HEADER_BYTES + AMS_ADDDEVICENOTIFICATION_REQUEST_DAT_BASE_BYTES);

	 memcpy(command_send.Ams_Header.AMSNetId_Target,  ctx->Ads_Register.AMSNetId_Target, sizeof(ctx->Ads_Register.AMSNetId_Target));
	 command_send.Ams_Header.AMSPort_Target = ctx->Ads_Register.AMSPort_Target;
	
	 memcpy(command_send.Ams_Header.AMSNetId_Source,  ctx->Ads_Register.AMSNetId_Source, sizeof(ctx->Ads_Register.AMSNetId_Source));
	 command_send.Ams_Header.AMSPort_Source = ctx->Ads_Register.AMSPort_Source;
	
	 command_send.Ams_Header.Command_Id = (uint16_t)ADS_CmdId_AddDeviceNotification;
	 
	 command_send.Ams_Header.State_Flags = (uint16_t)ADS_StateFlags_COMMAND;
	
	 command_send.Ams_Header.Data_Length = AMS_ADDDEVICENOTIFICATION_REQUEST_DAT_BASE_BYTES;     // 数据域长度
	
	 command_send.Ams_Header.Error_Code = (uint32_t)ADS_ErrorCode_NoError;
	 
	 command_send.Ams_Header.Invoke_Id = 1;       // 写多少都行


    command_send.Request.Index_Group = dat->Index_Group;
    
    command_send.Request.Index_Offset = dat->Index_Offset;
    
    command_send.Request.Lenth = dat->Lenth;

    command_send.Request.Transmission_Mode = dat->Transmission_Mode;

    command_send.Request.Max_Delay = dat->Max_Delay;

    command_send.Request.Cycle_Time = dat->Cycle_Time;

    memcpy(command_send.Request.Reserved , dat->Reserved, sizeof(command_send.Request.Reserved));

	 if(0 == ADS_AddDeciveNitification_BuildFrame(&command_send, send_buff, &send_lenth)) return 0;  
	 	 
	 LOG_RPINTF("send lenth: %d\n", send_lenth);
	 printf_array("send buff: ", send_buff, send_lenth);
	 if(0 == Ads_Tcp_Send(&ctx->Tcp_Register, send_buff, send_lenth)) return 0;

	 
	 if(0 == Ads_Tcp_Receive(&ctx->Tcp_Register, receive_buff, &receive_lenth)) return 0;
	 LOG_RPINTF("receive lenth: %d\n", receive_lenth);
	 printf_array("receive buff: ", receive_buff, receive_lenth);

	 if(0 == ADS_AddDeciveNitification_ResolevFrame(receive_buff, receive_lenth, &command_receive)) return 0;

    if(command_receive.Ams_Header.Error_Code != ADS_ErrorCode_NoError) return 0;
    if(command_receive.Receive.Result != ADS_ErrorCode_NoError) return 0;

    memcpy(&handle_of_notification, &command_receive.Receive.Notification_Handle, command_receive.Receive.Notification_Handle);

	 return 1;
}