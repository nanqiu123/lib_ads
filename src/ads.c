#include <stdint.h>
#include <string.h>
#include "../inc/ads.h"
#include "../inc/ads_tcp.h"
#include <stdint.h>
#include <stdlib.h>
#include "log.h"
ADS_Register S_Ads_register;


// 将四个 8 位无符号整数拼接成一个 32 位无符号整数
uint16_t combine_to_16_bigfirst(uint8_t byte, uint8_t byte1) {
    uint16_t result = 0;
    result |= ((uint16_t)byte1 << 8);
    result |= ((uint16_t)byte);
    return result;
}


uint32_t combine_to_32_bigfirst(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    uint32_t result = 0;
    // 将 byte1 放在最高字节
    result |= ((uint32_t)byte4 << 24);
    // 将 byte2 放在次高字节
    result |= ((uint32_t)byte3 << 16);
    // 将 byte3 放在次低字节
    result |= ((uint32_t)byte2 << 8);
    // 将 byte4 放在最低字节
    result |= ((uint32_t)byte1);
    return result;
}


// 将四个 8 位无符号整数拼接成一个 32 位无符号整数
uint32_t combine_to_32_LowFirst(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    uint32_t result = 0;
    // 将 byte1 放在最高字节
    result |= ((uint32_t)byte1 << 24);
    // 将 byte2 放在次高字节
    result |= ((uint32_t)byte2 << 16);
    // 将 byte3 放在次低字节
    result |= ((uint32_t)byte3 << 8);
    // 将 byte4 放在最低字节
    result |= ((uint32_t)byte4);
    return result;
}


static uint16_t little_to_big_endian_16(uint16_t num) 
{ 
	  num = ((num & 0xFF) << 8) | ((num & 0xFF00) >> 8);
    return num;
}

static uint32_t little_to_big_endian_32(uint32_t num) 
{
    num = ((num & 0xFF) << 24) | ((num & 0xFF00) << 8) | ((num & 0xFF0000) >> 8) | ((num & 0xFF000000) >> 24);	
		return num;
}

static uint16_t big_to_little_endian_16(uint16_t num) 
{ 
	  num = ((num & 0xFF) << 8) | ((num & 0xFF00) >> 8);
    return num;
}

static uint32_t big_to_little_endian_32(uint32_t num) 
{
    num = ((num & 0xFF) << 24) | ((num & 0xFF00) << 8) | ((num & 0xFF0000) >> 8) | ((num & 0xFF000000) >> 24);	
		return num;
}


// 反转数组的函数
void reverseArray(uint8_t arr[], int size)
{
    uint8_t temp;
    int start = 0;
    int end = size/2;

    for(int i = 0; i < end; i++)
	{
		temp = arr[start];
		arr[start] = arr[size - 1 - start];
		arr[size - 1 - start] = temp;
		start++;
    }
}


int printf_array(char *front_str, char *arr, uint16_t lenth)
{
    LOG_RPINTF(front_str);
    for (int i = 0; i < lenth; i++) 
    {
        LOG_RPINTF("0x%02x ", (unsigned char)arr[i]);
    }
    LOG_RPINTF("\n");
}

/*
     ADS协议 设置当前的IP 端口 
	 输入参数： target_net_id_port: 目标ip、端口； sender_net_id_port ：本机ip、端口；
	 输出参数： 1成功， 0失败
*/
char ADS_Open(uint8_t *tcp_ip, uint16_t tcp_port)
{
	return ADS_Tcp_Connect(tcp_ip, tcp_port);
}

/*
     ADS协议 设置当前的IP 端口 
	 输入参数： target_net_id_port: 目标ip、端口； sender_net_id_port ：本机ip、端口；
	 输出参数： 1成功， 0失败
*/
char ADS_Close(uint8_t *tcp_ip, uint16_t tcp_port)
{
	return ADS_Tcp_Close();
}

/*
     ADS协议 设置当前的IP 端口 
	 输入参数： target_net_id_port: 目标ip、端口； sender_net_id_port ：本机ip、端口；
	 输出参数： 1成功， 0失败
	 
*/
char ADS_SetIdPort(uint8_t *target_net_id_port, uint8_t *sender_net_id_port)
{
	 if(target_net_id_port == NULL || sender_net_id_port == NULL) return 0;
	
	 uint8_t str[50] = {0};
	 strcpy((char *)str, target_net_id_port);
	 char *id = strtok((char *)str, ":");
	 char *port = strtok(NULL, ":");
	 
	 S_Ads_register.AMS_Target_Net_ID[0] = atoi(strtok(id, "."));
	 for(int i = 1; i < 6; i ++)
     S_Ads_register.AMS_Target_Net_ID[i] = atoi(strtok(NULL, "."));  
	
	 S_Ads_register.AMS_Target_Port = atoi(port); 
	
	 strcpy((char *)str, sender_net_id_port);
	 id = strtok(str, ":");
	 port = strtok(NULL, ":");
	
	 S_Ads_register.AMS_Sender_Net_ID[0] = atoi(strtok(id, "."));
	 for(int i = 1; i < 6; i ++)
     S_Ads_register.AMS_Sender_Net_ID[i] = atoi(strtok(NULL, "."));  
	
	 S_Ads_register.AMS_Sender_Port = atoi(port); 
	 
	 return 1;
}

/*
     ADS_Write
	 输入参数： gpoup_index： 区域， index_offset： 地址， dat：数据， lenth 数据长度
	 输出参数： 1成功， 0失败
*/
// 00 00 24 00 00 00 0A 64 AE 1F 01 01 82 FC 0A 64 AD 02 01 01 53 03 03 00 05 00 04 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00
char ADS_Write(ADS_GroupIndex gpoup_index, uint64_t index_offset, uint8_t *dat, uint64_t lenth)
{
     ADS_Write_Request_Send command_send;
	
	 uint8_t buff[256] = {0};
	 uint8_t response_buff[1024] = {0};
	 uint16_t response_lenth = 0;
	 
	 if(dat == NULL || lenth <= 0) return 0;
	
	 memcpy(command_send.AMS_Target_Net_ID,  S_Ads_register.AMS_Target_Net_ID, 6);
	 command_send.AMS_Target_Port = S_Ads_register.AMS_Target_Port;
	
	 memcpy(command_send.AMS_Sender_Net_ID,  S_Ads_register.AMS_Sender_Net_ID, 6);
	 command_send.AMS_Sender_Port = S_Ads_register.AMS_Sender_Port;
	
	 command_send.CmdId = (uint16_t)ADS_CmdIdWrite;
	 
	 command_send.StateFlags = ADS_COMMAND;
	
	 command_send.cbData = 4 + 4  + 4 + lenth;
	
	 command_send.ErrorCode = 0x00000000;
	 
	 command_send.InvokeId = 1; // 写多少都行
	 
	 command_send.Write_Request.IndexGroup = gpoup_index;
	 
	 command_send.Write_Request.IndexOffset = index_offset;
	 
	 command_send.Write_Request.CbLength = lenth;
	 
	 command_send.Write_Request.Data = &(dat[0]);
	 
	 
   uint16_t i = 6; // 留出起始6个字节 
	 
	 memcpy(&buff[i], command_send.AMS_Target_Net_ID, 6);
	 buff[i += 6] =  little_to_big_endian_16(command_send.AMS_Target_Port) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.AMS_Target_Port);
	 
	 memcpy(&buff[i += 1], command_send.AMS_Sender_Net_ID, 6);
	 buff[i += 6] =  little_to_big_endian_16(command_send.AMS_Sender_Port) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.AMS_Sender_Port);
	 
	 buff[i += 1] =  little_to_big_endian_16(command_send.CmdId) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.CmdId);
	 
	 buff[i += 1] =  little_to_big_endian_16(command_send.StateFlags) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.StateFlags);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexGroup) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexGroup) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexGroup) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexGroup);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexOffset) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexOffset) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexOffset) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexOffset);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.CbLength) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.CbLength) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.CbLength) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.CbLength);
	 
	 for(uint32_t n = 0; n < command_send.Write_Request.CbLength; n ++)
	 {
			 buff[i += 1] =  command_send.Write_Request.Data[n];
	 }
	 
	 i += 1;
	 
	 buff[0] =  0;
	 buff[1] =  0;
	 buff[2] =  little_to_big_endian_32(i - 6) >> 24;
	 buff[3] =  little_to_big_endian_32(i - 6) >> 16;
	 buff[4] =  little_to_big_endian_32(i - 6) >> 8;
	 buff[5] =  little_to_big_endian_32(i - 6); 
	 
	 
	 LOG_RPINTF("send lenth: %d\n", i);
	 printf_array("send buff: ", buff, i);
	 Ads_Tcp_Send(buff, i);

	 uint16_t receive_lenth = 0;
	 
	 Ads_Tcp_Receive(response_buff, &receive_lenth);

	 LOG_RPINTF("read lenth: %d\n", receive_lenth);
	 printf_array("read buff: ", response_buff, receive_lenth);

	 if(receive_lenth  <= 32) return 0;
	 if(response_buff[receive_lenth - 1] != 0 || response_buff[receive_lenth - 2] != 0 || response_buff[receive_lenth - 3] != 0 || response_buff[receive_lenth - 4] != 0) return 0;
	 
	 return 1;
}

/*
     ADS协议 读取函数
	 输入参数： gpoup_index： 区域， index_offset： 地址， lenth： 数据长度， dat：数据， return_lenth 返回数据长度
	 输出参数： 1成功， 0失败
*/
char ADS_Read(ADS_GroupIndex gpoup_index, uint64_t index_offset, uint64_t lenth, uint8_t *dat, uint16_t *return_lenth)
{
    ADS_Write_Request_Send command_send;
	
	 uint8_t buff[256] = {0};
	 uint8_t response_buff[256] = {0};
	 uint16_t response_lenth = 0;
	 
	 if(lenth <= 0) return 0;
	
	 memcpy(command_send.AMS_Target_Net_ID,  S_Ads_register.AMS_Target_Net_ID, 6);
	 command_send.AMS_Target_Port = S_Ads_register.AMS_Target_Port;
	
	 memcpy(command_send.AMS_Sender_Net_ID,  S_Ads_register.AMS_Sender_Net_ID, 6);
	 command_send.AMS_Sender_Port = S_Ads_register.AMS_Sender_Port;
	
	 command_send.CmdId = (uint16_t)ADS_CmdIdRead;
	 
	 command_send.StateFlags = ADS_COMMAND;
	
	 command_send.cbData = 4 + 4  + 4;
	
	 command_send.ErrorCode = ADS_NoError;
	 
	 command_send.InvokeId = 1; // 写多少都行
	 
	 command_send.Write_Request.IndexGroup = gpoup_index;
	 
	 command_send.Write_Request.IndexOffset = index_offset;
	 
	 command_send.Write_Request.CbLength = lenth;
	 
	 command_send.Write_Request.Data = &(dat[0]);
	 
	 
   uint16_t i = 6; // 留出起始6个字节 
	 
	 memcpy(&buff[i], command_send.AMS_Target_Net_ID, 6);
	 buff[i += 6] =  little_to_big_endian_16(command_send.AMS_Target_Port) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.AMS_Target_Port);
	 
	 memcpy(&buff[i += 1], command_send.AMS_Sender_Net_ID, 6);
	 buff[i += 6] =  little_to_big_endian_16(command_send.AMS_Sender_Port) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.AMS_Sender_Port);
	 
	 buff[i += 1] =  little_to_big_endian_16(command_send.CmdId) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.CmdId);
	 
	 buff[i += 1] =  little_to_big_endian_16(command_send.StateFlags) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.StateFlags);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexGroup) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexGroup) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexGroup) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexGroup);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexOffset) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexOffset) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexOffset) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.IndexOffset);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.CbLength) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.CbLength) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.CbLength) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Write_Request.CbLength);
	 
	 i += 1;
	 
	 buff[0] =  0;
	 buff[1] =  0;
	 buff[2] =  little_to_big_endian_32(i - 6) >> 24;
	 buff[3] =  little_to_big_endian_32(i - 6) >> 16;
	 buff[4] =  little_to_big_endian_32(i - 6) >> 8;
	 buff[5] =  little_to_big_endian_32(i - 6); 
	 
	 
	 LOG_RPINTF("send lenth: %d\n", i);
	 printf_array("send buff: ", buff, i);
	 Ads_Tcp_Send(buff, i);

	 uint16_t receive_lenth = 0;
	 
	 Ads_Tcp_Receive(response_buff, &receive_lenth);

	 LOG_RPINTF("read lenth: %d\n", receive_lenth);
	 printf_array("read buff: ", response_buff, receive_lenth);

	 if(receive_lenth  <= 32) return 0;
		 
	 uint16_t n = 6;	 
	 ADS_Read_Request_Receive command_receive;
	 memset((uint8_t *)&command_receive, 0, sizeof(ADS_Read_Request_Receive));
	 
	 memcpy(command_receive.AMS_Target_Net_ID, &response_buff[n], 6);
	 n += 6;
	 
	 command_receive.AMS_Target_Port = (response_buff[n + 1] << 8) | response_buff[n];
	 n += 2;
	 
	 memcpy(command_send.AMS_Sender_Net_ID, &response_buff[n], 6);
	 n += 6;
	 command_receive.AMS_Sender_Port = (response_buff[n + 1] << 8) | response_buff[n];
	 n += 2;
	 
	 command_receive.CmdId = (response_buff[n + 1] << 8) | response_buff[n];
	 n += 2;
	 
	 command_receive.StateFlags = (response_buff[n + 1] << 8) | response_buff[n];
	 n += 2;
	 
	 command_receive.cbData = (response_buff[n + 3] << 24) | (response_buff[n + 2] << 16) | (response_buff[n + 1] << 8) | (response_buff[n]);
	 n += 4;
	 
	 command_receive.ErrorCode = (response_buff[n + 3] << 24) | (response_buff[n + 2] << 16) | (response_buff[n + 1] << 8) | (response_buff[n]);
	 n += 4;
	 
	 command_receive.InvokeId = (response_buff[n + 3] << 24) | (response_buff[n + 2] << 16) | (response_buff[n + 1] << 8) | (response_buff[n]);
	 n += 4;

	 command_receive.Read_Response.Result = (response_buff[n + 3] << 24) | (response_buff[n + 2] << 16) | (response_buff[n + 1] << 8) | (response_buff[n]);
	 n += 4;
	 
	 command_receive.Read_Response.CbLength = (response_buff[n + 3] << 24) | (response_buff[n + 2] << 16) | (response_buff[n + 1] << 8) | (response_buff[n]);
	 n += 4;
	  
		
	 if( command_receive.Read_Response.Result != 0) return 0;
	 
 	 uint32_t m = 0;	
	 for(; m < command_send.Write_Request.CbLength; m ++)
	 {
			 dat[m] = response_buff[n + m];
	 }
	 *return_lenth = m;
	 
	 return 1;
}

/*
     ADS协议   ReadWrite
	 输入参数： value_name 
	 输出参数： 1成功， 0失败
*/
char ADS_ReadWrite(uint8_t *value_name, uint8_t *return_dat)
{
     ADS_ReadWrite_Request_Send command_send;
	
	 uint8_t buff[512] = {0};
	 uint8_t response_buff[512] = {0};
	 uint16_t response_lenth = 0;
	 uint16_t lenth = strlen((char *)value_name) + 1;

	 if(value_name == NULL) return 0;
	
	 memcpy(command_send.AMS_Target_Net_ID,  S_Ads_register.AMS_Target_Net_ID, 6);
	 command_send.AMS_Target_Port = S_Ads_register.AMS_Target_Port;
	
	 memcpy(command_send.AMS_Sender_Net_ID,  S_Ads_register.AMS_Sender_Net_ID, 6);
	 command_send.AMS_Sender_Port = S_Ads_register.AMS_Sender_Port;
	
	 command_send.CmdId = (uint16_t)ADS_CmdIdReadWrite;
	 
	 command_send.StateFlags = ADS_COMMAND;
	
	 command_send.cbData = 4 + 4 + 4 + 4 + lenth;
	
	 command_send.ErrorCode = ADS_NoError;
	 
	 command_send.InvokeId = 1; // 写多少都行
	 
	 command_send.Request.IndexGroup = ADS_HANDLE;
	 
	 command_send.Request.IndexOffset = 0;
	 
	 command_send.Request.CbReadLength = 4;
	 
	 command_send.Request.CbWriteLength = lenth;

	 command_send.Request.Date = &(value_name[0]);
	 
	 
     uint16_t i = 6; // 留出起始6个字节 
	 
	 memcpy(&buff[i], command_send.AMS_Target_Net_ID, 6);
	 buff[i += 6] =  little_to_big_endian_16(command_send.AMS_Target_Port) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.AMS_Target_Port);
	 
	 memcpy(&buff[i += 1], command_send.AMS_Sender_Net_ID, 6);
	 buff[i += 6] =  little_to_big_endian_16(command_send.AMS_Sender_Port) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.AMS_Sender_Port);
	 
	 buff[i += 1] =  little_to_big_endian_16(command_send.CmdId) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.CmdId);
	 
	 buff[i += 1] =  little_to_big_endian_16(command_send.StateFlags) >> 8;
	 buff[i += 1] =  little_to_big_endian_16(command_send.StateFlags);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.cbData);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.ErrorCode);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.InvokeId);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.IndexGroup) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.IndexGroup) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.IndexGroup) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.IndexGroup);
	  
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.IndexOffset) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.IndexOffset) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.IndexOffset) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.IndexOffset);
	 
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.CbReadLength) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.CbReadLength) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.CbReadLength) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.CbReadLength);

	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.CbWriteLength) >> 24;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.CbWriteLength) >> 16;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.CbWriteLength) >> 8;
	 buff[i += 1] =  little_to_big_endian_32(command_send.Request.CbWriteLength);
	 
	 for(uint32_t n = 0; n < command_send.Request.CbWriteLength; n ++)
	 {
			 buff[i += 1] =  command_send.Request.Date[n];
	 }
	 
	 i += 1;
	 
	 buff[0] =  0;
	 buff[1] =  0;
	 buff[2] =  little_to_big_endian_32(i - 6) >> 24;
	 buff[3] =  little_to_big_endian_32(i - 6) >> 16;
	 buff[4] =  little_to_big_endian_32(i - 6) >> 8;
	 buff[5] =  little_to_big_endian_32(i - 6); 
	 
	 LOG_RPINTF("send lenth: %d\n", i);
	 printf_array("send buff: ", buff, i);
	 Ads_Tcp_Send(buff, i);

	 uint16_t receive_lenth = 0;
	 
	 Ads_Tcp_Receive(response_buff, &receive_lenth);

	 LOG_RPINTF("read lenth: %d\n", receive_lenth);
	 printf_array("read buff: ", response_buff, receive_lenth);

	 if(receive_lenth  <= 32) return 0;

	 uint16_t n = 6;	 
	 ADS_ReadWrite_Request_Receive command_receive;
	 memset((uint8_t *)&command_receive, 0, sizeof(command_receive));
	 
	 memcpy(command_receive.AMS_Target_Net_ID, &response_buff[n], 6);
	 n += 6;
	 
	 command_receive.AMS_Target_Port = combine_to_16_bigfirst(response_buff[n], response_buff[n + 1]);
	 n += 2;
	 
	 memcpy(command_send.AMS_Sender_Net_ID, &response_buff[n], 6);
	 n += 6;
	 
	 command_receive.AMS_Sender_Port = combine_to_16_bigfirst(response_buff[n], response_buff[n + 1]);
	 n += 2;	

	 command_receive.CmdId = combine_to_16_bigfirst(response_buff[n], response_buff[n + 1]);
	 n += 2;
	 
	 command_receive.StateFlags = combine_to_16_bigfirst(response_buff[n], response_buff[n + 1]);
	 n += 2;
	 
	 command_receive.cbData = combine_to_32_bigfirst(response_buff[n], response_buff[n + 1],response_buff[n + 2], response_buff[n + 3]);
	 n += 4;
	 
	 command_receive.ErrorCode = combine_to_32_bigfirst(response_buff[n], response_buff[n + 1],response_buff[n + 2], response_buff[n + 3]);
	 n += 4;
	 
	 command_receive.InvokeId = combine_to_32_bigfirst(response_buff[n], response_buff[n + 1],response_buff[n + 2], response_buff[n + 3]);
	 n += 4;
	  		
	 command_receive.Response.Result = combine_to_32_bigfirst(response_buff[n], response_buff[n + 1],response_buff[n + 2], response_buff[n + 3]);
	 n += 4;

	 command_receive.Response.CbLength = combine_to_32_bigfirst(response_buff[n], response_buff[n + 1],response_buff[n + 2], response_buff[n + 3]);
	 n += 4;

	 if(command_receive.ErrorCode != (uint32_t)ADS_NoError) return 0;

	 return_dat[0] = response_buff[n];
	 return_dat[1] = response_buff[n + 1];
	 return_dat[2] = response_buff[n + 2];
	 return_dat[3] = response_buff[n + 3];
	 
	 return 1;
}

// 函数：将十六进制字节数组转换为浮点数
float hex_to_float(uint8_t *hex) {
    union {
        uint32_t i;
        float f;
    } u;
    // 将字节数组组合成一个 32 位无符号整数
    u.i = ((uint32_t)hex[0] << 24) | ((uint32_t)hex[1] << 16) | ((uint32_t)hex[2] << 8) | (uint32_t)hex[3];
    // 将 32 位无符号整数解释为浮点数
    return u.f;
}


/*
     ADS协议   ReadWrite Read
	 输入参数： value_name 
	 输出参数： 1成功， 0失败
*/
char ADS_ReadWrite_Read(uint8_t *value_name, uint16_t read_lenth, uint8_t *return_dat, uint16_t *return_lenth)
{
	uint8_t receive[4] = {0};
	uint64_t handle = 0;
	int sta = 0;


	LOG_RPINTF("\r\n%s read start\r\n", value_name);


	sta = ADS_ReadWrite(value_name, receive);
	LOG_RPINTF("read handle status: %d\r\n", sta);
	printf_array("handle: ", receive, 4);
	if(!sta) return 0;

	handle = combine_to_32_bigfirst(receive[0], receive[1], receive[2], receive[3]);
	sta = ADS_Read(ADS_HANDLE_FOR_VALUE, handle, read_lenth, return_dat, return_lenth);
	LOG_RPINTF("read data status: %d\r\n", sta);
	printf("return_lenth: %d\r\n", *return_lenth);
	printf_array("data: ", return_dat, *return_lenth);
	reverseArray(return_dat, *return_lenth);
	printf_array("data: ", return_dat, *return_lenth);
	LOG_RPINTF("dat_to_float: %f\r\n", hex_to_float(return_dat));
	LOG_RPINTF("dat_to_string: %s\r\n", return_dat);
	LOG_RPINTF("dat_to_int: %d\r\n", *(int *)return_dat);
	LOG_RPINTF("read over\r\n\r\n");
	if(!sta) return 0;


	return ;
}

