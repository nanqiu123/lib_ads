
#include <string.h>
#include "../inc/ads_tools.h"
#include "../inc/ads_typedef.h"
#include "../inc/ads_log.h"

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

   LittleEndianIntergerToHex_ByLittleEndian(Ams_Header->AMSPort_Source, sizeof(Ams_Header->AMSPort_Source), &command_frame[index]);
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
	 输入参数：  ( uint8_t *command_frame, AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header)
	 输出参数： 1成功， 0失败
*/
char ADS_Header_ResolveFrame( uint8_t *command_frame, AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header)
{
   uint16_t index = 0;


   if(Ams_Tcp_Header == NULL || Ams_Header == NULL || command_frame == NULL ) return 0;
   
  
   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Tcp_Header->Reserved, sizeof(Ams_Tcp_Header->Reserved));
   index += sizeof(Ams_Tcp_Header->Reserved);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Tcp_Header->Command_Lenth, sizeof(Ams_Tcp_Header->Command_Lenth));
   index += sizeof(Ams_Tcp_Header->Command_Lenth);

   memcpy(&Ams_Header->AMSNetId_Target, &command_frame[index], sizeof(Ams_Header->AMSNetId_Target));
   index += sizeof(Ams_Header->AMSNetId_Target);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Header->AMSPort_Target, sizeof(Ams_Header->AMSPort_Target));
   index += sizeof(Ams_Header->AMSPort_Target);

   memcpy(&Ams_Header->AMSNetId_Source, &command_frame[index], sizeof(Ams_Header->AMSNetId_Source));
   index += sizeof(Ams_Header->AMSNetId_Source);

   BigEndianHexToInterger_ByLittleEndian(&command_frame[index], (uint64_t *)&Ams_Header->AMSPort_Source, sizeof(Ams_Header->AMSPort_Source));
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


/*
    打印AMS_TCP_Header_t和AMS_Header_t
	 输入参数： AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header
	 输出参数： 1成功， 0失败
*/
char ADS_Header_Printf(AMS_TCP_Header_t *Ams_Tcp_Header, AMS_Header_t *Ams_Header)
{
   uint16_t index = 0;

   if(Ams_Tcp_Header == NULL || Ams_Header == NULL ) return 0;
   
   LOG_RPINTF("Ams_Tcp_Header->Reserved: %d\r\n", Ams_Tcp_Header->Reserved);
   LOG_RPINTF("Ams_Tcp_Header->Command_Lenth:  %d\r\n",Ams_Tcp_Header->Command_Lenth);
   LOG_RPINTF("Ams_Header->AMSNetId_Target: %d.%d.%d.%d.%d.%d\r\n",
    Ams_Header->AMSNetId_Target[0],
    Ams_Header->AMSNetId_Target[1],
    Ams_Header->AMSNetId_Target[2],
    Ams_Header->AMSNetId_Target[3],
    Ams_Header->AMSNetId_Target[4],
    Ams_Header->AMSNetId_Target[5]
    );
   LOG_RPINTF("Ams_Header->AMSPort_Target: %d\r\n", Ams_Header->AMSPort_Target);
   LOG_RPINTF("Ams_Header->AMSNetId_Source: %d.%d.%d.%d.%d.%d\r\n",
    Ams_Header->AMSNetId_Source[0],
    Ams_Header->AMSNetId_Source[1],
    Ams_Header->AMSNetId_Source[2],
    Ams_Header->AMSNetId_Source[3],
    Ams_Header->AMSNetId_Source[4],
    Ams_Header->AMSNetId_Source[5]
    );
   LOG_RPINTF("Ams_Header->AMSPort_Source: %d\r\n", Ams_Header->AMSPort_Source);
   LOG_RPINTF("Ams_Header->Command_Id: 0x%02x\r\n", Ams_Header->Command_Id);
   LOG_RPINTF("Ams_Header->State_Flags: 0x%04x\r\n", Ams_Header->State_Flags);
   LOG_RPINTF("Ams_Header->Data_Length: %d\r\n", Ams_Header->Data_Length);
   LOG_RPINTF("Ams_Header->Error_Code: 0x%04x\r\n", Ams_Header->Error_Code);
   LOG_RPINTF("Ams_Header->Invoke_Id: %d\r\n", Ams_Header->Invoke_Id);
   

   return 1;
}
