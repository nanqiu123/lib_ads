#include <stdlib.h>
#include <string.h>
#include "../inc/ads_Read.h"
#include "../inc/ads_tcp.h"
#include "../inc/ads_tools.h"
#include "../inc/ads_base.h"
#include "../inc/log.h"


/*
    组帧
	 输入参数：  (ADS_Read_Request_t *command, uint8_t *command_frame, uint16_t *command_lenth)
	 输出参数： 1成功， 0失败
*/
static char ADS_Read_BuildFrame(ADS_Read_Request_t *command, uint8_t *command_frame, uint16_t *command_lenth)
{
   uint16_t index = 0;
   if(command == NULL || command_frame == NULL) return 0;
   if(0 == ADS_Header_BuildFrame(&command->Ams_Tcp_Header, &command->Ams_Header, command_frame, &index)) return  0;

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Index_Group, sizeof(command->Request.Index_Group),&command_frame[index]);
   index += sizeof(command->Request.Index_Group);

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Index_Offset, sizeof(command->Request.Index_Offset),&command_frame[index]);
   index += sizeof(command->Request.Index_Offset);

   LittleEndianIntergerToHex_ByBigEndian(command->Request.Lenth, sizeof(command->Request.Lenth),&command_frame[index]);
   index += sizeof(command->Request.Lenth);

   *command_lenth = index;
   return 1;
}


/*
     Read 解析帧
	 输入参数： uint8_t *command_frame, uint16_t command_lenth, ADS_Read_Request_t *command)
	 输出参数： 1成功， 0失败
*/
char ADS_Read_ResolevFrame(uint8_t *command_frame, uint16_t command_lenth, ADS_Read_Receive_t *command)
{
   uint16_t index = 0;
   if(command == NULL || command_frame == NULL) return 0;

   if(command_lenth <= AMS_HEADER_BYTES) return 0;
   if(command_frame[0] != 0 || command_frame[1] != 0) return 0;

   if(0 == ADS_Header_ResolveFrame(command_frame, command_lenth, &command->Ams_Tcp_Header, &command->Ams_Header)) return 0;  

   index += AMS_HEADER_BYTES;

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index],  (uint64_t *)&command->Receive.Result, sizeof(command->Receive.Result));
   index += sizeof(command->Receive.Result);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index],  (uint64_t *)&command->Receive.Lenth, sizeof(command->Receive.Lenth));
   index += sizeof(command->Receive.Lenth);
   
   memcpy(&command->Receive.Data, &command_frame[index], command->Receive.Lenth);

   if(0 == check_endianness())
   {
      reverseArray(command->Receive.Data, command->Receive.Lenth);
   }

   return 1;
}


/*
     ADS_Read
	 输入参数： ctx: 句柄， gpoup_index： 区域， index_offset： 地址， dat：数据， *lenth 数据长度
	 输出参数： 1成功， 0失败
*/
char ADS_Read(Ads_Handle_t *ctx ,ADS_GroupIndex_t gpoup_index, uint64_t index_offset, uint8_t *dat, uint64_t *lenth)
{
    ADS_Read_Request_t command_send;
	 ADS_Read_Receive_t command_receive;
	
	 uint8_t send_buff[1024] = {0};
	 uint16_t send_lenth = 0;
	 
    uint8_t receive_buff[1024] = {0};
	 uint16_t receive_lenth = 0;


	 if(ctx == NULL || dat == NULL || lenth <= 0) return 0;
	
	 command_send.Ams_Tcp_Header.Reserved = 0;
	 command_send.Ams_Tcp_Header.Command_Lenth = (uint32_t)(AMS_HEADER_BYTES + AMS_READ_REQUEST_BASE_BYTES + *lenth);

	 memcpy(command_send.Ams_Header.AMSNetId_Target,  ctx->Ads_Register.AMSNetId_Target, sizeof(ctx->Ads_Register.AMSNetId_Target));
	 command_send.Ams_Header.AMSPort_Target = ctx->Ads_Register.AMSPort_Target;
	
	 memcpy(command_send.Ams_Header.AMSNetId_Source,  ctx->Ads_Register.AMSNetId_Source, sizeof(ctx->Ads_Register.AMSNetId_Source));
	 command_send.Ams_Header.AMSPort_Source = ctx->Ads_Register.AMSPort_Source;
	
	 command_send.Ams_Header.Command_Id = (uint16_t)ADS_CmdId_Read;
	 
	 command_send.Ams_Header.State_Flags = (uint16_t)ADS_StateFlags_COMMAND;
	
	 command_send.Ams_Header.Data_Length = AMS_READ_REQUEST_BASE_BYTES + *lenth;     // 数据域长度
	
	 command_send.Ams_Header.Error_Code = (uint32_t)ADS_ErrorCode_NoError;
	 
	 command_send.Ams_Header.Invoke_Id = 1;       // 写多少都行


    command_send.Request.Index_Group = (uint32_t)gpoup_index;
    
    command_send.Request.Index_Offset = (uint32_t)index_offset;
    
    command_send.Request.Lenth = (uint32_t)*lenth;
    
	 if(0 == ADS_Read_BuildFrame(&command_send, send_buff, &send_lenth)) return 0;  
	 	 
	 LOG_RPINTF("send lenth: %d\n", send_lenth);
	 printf_array("send buff: ", send_buff, send_lenth);
	 if(0 == Ads_Tcp_Send(&ctx->Tcp_Register, send_buff, send_lenth)) return 0;

	 
	 if(0 == Ads_Tcp_Receive(&ctx->Tcp_Register, receive_buff, &receive_lenth)) return 0;
	 LOG_RPINTF("read lenth: %d\n", receive_lenth);
	 printf_array("read buff: ", receive_buff, receive_lenth);

    command_receive.Receive.Data = dat;
	 if(0 == ADS_Read_ResolevFrame(receive_buff, receive_lenth, &command_receive)) return 0;

    if(command_receive.Ams_Header.Error_Code != ADS_ErrorCode_NoError) return 0;
    if(command_receive.Receive.Result != ADS_ErrorCode_NoError) return 0;

    memcpy(dat, command_receive.Receive.Data, command_receive.Receive.Lenth);
    *lenth =  command_receive.Receive.Lenth;

     

	 return 1;
}