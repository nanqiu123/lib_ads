
#include <string.h>
#include "../inc/ads_tools.h"
#include "../inc/ads_typdef.h"

/*
     ADS_Header_BuildFrame
	 输入参数： AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header, 返回值：uint8_t *command_frame, uint16_t *command_lenth
	 输出参数： 1成功， 0失败
*/
char ADS_Header_BuildFrame(AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header, uint8_t *command_frame, uint16_t *command_lenth)
{
   uint16_t index = 0;

   if(Ams_Tcp_Header == NULL || Ams_Header == NULL || command_frame == NULL) return 0;
   
   
   LittleEndianIntergerToHex_ByBigEndian(Ams_Tcp_Header->Reserved, sizeof(Ams_Tcp_Header->Reserved), &command_frame[index]);
   index += sizeof(Ams_Tcp_Header->Reserved);

   LittleEndianIntergerToHex_ByBigEndian(Ams_Tcp_Header->Command_Lenth, sizeof(Ams_Tcp_Header->Command_Lenth), &command_frame[index]);
   index += sizeof(Ams_Tcp_Header->Command_Lenth);



   memcpy(&command_frame[index], Ams_Header->AMSNetId_Target, sizeof(Ams_Header->AMSNetId_Target));
   index += sizeof(Ams_Header->AMSNetId_Target);

   LittleEndianIntergerToHex_ByLittleEndian(Ams_Header->AMSPort_Target, sizeof(Ams_Header->AMSPort_Target), &command_frame[index]);
   index += sizeof(Ams_Header->AMSPort_Target);

   memcpy(&command_frame[index], Ams_Header->AMSNetId_Source, sizeof(Ams_Header->AMSNetId_Source));
   index += sizeof(Ams_Header->AMSNetId_Source);

   LittleEndianIntergerToHex_ByLittleEndian(Ams_Header->AMSPort_Target, sizeof(Ams_Header->AMSPort_Target), &command_frame[index]);
   index += sizeof(Ams_Header->AMSPort_Source);

   LittleEndianIntergerToHex_ByBigEndian(Ams_Header->Command_Id, sizeof(Ams_Header->Command_Id), &command_frame[index]);
   index += sizeof(Ams_Header->Command_Id);

   LittleEndianIntergerToHex_ByBigEndian(Ams_Header->State_Flags, sizeof(Ams_Header->State_Flags), &command_frame[index]);
   index += sizeof(Ams_Header->State_Flags);

   LittleEndianIntergerToHex_ByBigEndian(Ams_Header->Data_Length, sizeof(Ams_Header->Data_Length), &command_frame[index]);
   index += sizeof(Ams_Header->Data_Length);

   LittleEndianIntergerToHex_ByBigEndian(Ams_Header->Error_Code, sizeof(Ams_Header->Error_Code), &command_frame[index]);
   index += sizeof(Ams_Header->Error_Code);

   LittleEndianIntergerToHex_ByBigEndian(Ams_Header->Invoke_Id, sizeof(Ams_Header->Invoke_Id), &command_frame[index]);
   index += sizeof(Ams_Header->Invoke_Id);

   *command_lenth = index;

   return 1;
}


/*
     ADS_Header_ResolveFrame
	 输入参数：  uint8_t *command_frame, uint16_t command_lenth 返回值：AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header
	 输出参数： 1成功， 0失败
*/
char ADS_Header_ResolveFrame( uint8_t *command_frame, uint16_t command_lenth, AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header)
{
   uint16_t index = 0;

   if(Ams_Tcp_Header == NULL || Ams_Header == NULL || command_frame == NULL ) return 0;
   
   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Tcp_Header->Reserved, sizeof(Ams_Tcp_Header->Reserved));
   index += sizeof(Ams_Tcp_Header->Reserved);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Tcp_Header->Command_Lenth, sizeof(Ams_Tcp_Header->Command_Lenth));
   index += sizeof(Ams_Tcp_Header->Command_Lenth);


   memcpy(&command_frame[index], Ams_Header->AMSNetId_Target, sizeof(Ams_Header->AMSNetId_Target));
   index += sizeof(Ams_Header->AMSNetId_Target);

   LittleEndianIntergerToHex_ByLittleEndian(Ams_Header->AMSPort_Target, sizeof(Ams_Header->AMSPort_Target), &command_frame[index]);
   index += sizeof(Ams_Header->AMSPort_Target);

   memcpy(&command_frame[index], Ams_Header->AMSNetId_Source, sizeof(Ams_Header->AMSNetId_Source));
   index += sizeof(Ams_Header->AMSNetId_Source);

   LittleEndianIntergerToHex_ByLittleEndian(Ams_Header->AMSPort_Target, sizeof(Ams_Header->AMSPort_Target), &command_frame[index]);
   index += sizeof(Ams_Header->AMSPort_Source);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Header->Command_Id, sizeof(Ams_Header->Command_Id));
   index += sizeof(Ams_Header->Command_Id);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Header->State_Flags, sizeof(Ams_Header->State_Flags));
   index += sizeof(Ams_Header->State_Flags);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Header->Data_Length, sizeof(Ams_Header->Data_Length));
   index += sizeof(Ams_Header->Data_Length);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Header->Error_Code, sizeof(Ams_Header->Error_Code));
   index += sizeof(Ams_Header->Error_Code);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Header->Invoke_Id, sizeof(Ams_Header->Invoke_Id));
   index += sizeof(Ams_Header->Invoke_Id);

   return 1;
}


