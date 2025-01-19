#ifndef _ADS_H_
#define _ADS_H_

#include "stdint.h"

typedef enum
{
	ADS_CmdIdReadDeviceInfo = 0x0001, 
	ADS_CmdIdRead,
	ADS_CmdIdWrite, 
	ADS_CmdIdReadState,
	ADS_CmdIdWriteControl,
	ADS_CmdIdAddDeviceNotification,
    ADS_CmdIdDeleteDeviceNotification,
    ADS_CmdIdDeviceNotification,
	ADS_CmdIdReadWrite,
}AMS_CmdId;

typedef enum
{	
	ADS_REQUEST  = 0x0000,
	ADS_RESPONSE = 0x0001, 
	ADS_COMMAND  = 0x0004, 
}AMS_StateFlags;

typedef enum
{						 
	 ADS_M  = 0x00004020,      
	 ADS_MX = 0x00004021,    
	 ADS_I  = 0x0000F020,      
	 ADS_IX = 0x0000F021, 
	 ADS_Q  = 0x0000F030, 
	 ADS_QX = 0X0000f0310, 
	 ADS_HANDLE = 0x0000F003, 
	 ADS_HANDLE_FOR_VALUE = 0x0000F005,  
	 ADS_RELEASE_HANDLE = 0x0000F006
} ADS_GroupIndex;

typedef enum
{						 
	 ADS_NoError  = 0x00000000,      
} ADS_ErrorCode;

typedef struct 
{
     uint32_t IndexGroup;         // 区
	 uint32_t IndexOffset;        // 地址
	 uint32_t CbLength;           // 数据长度
	 uint8_t  *Data;              // 数据（由于字节大小不固定，所以设置指针）
}ADS_WriteRequest_Typedef;


typedef struct 
{
	 uint32_t ErrorCode;
}ADS_WriteResponse_Typedef;


typedef struct 
{
    uint8_t  AMS_Target_Net_ID[6];
	uint16_t AMS_Target_Port;
	uint8_t  AMS_Sender_Net_ID[6];
	uint16_t AMS_Sender_Port;
	
	uint16_t CmdId;
	
	uint16_t StateFlags;
	uint32_t cbData;          // 数据区域的字节长度
	uint32_t ErrorCode;
	uint32_t InvokeId;
	
	ADS_WriteRequest_Typedef Write_Request;
} ADS_Write_Request_Send;           // 发送写入命令


typedef struct 
{
    uint8_t  AMS_Target_Net_ID[6];
	uint16_t AMS_Target_Port;
	uint8_t  AMS_Sender_Net_ID[6];
	uint16_t AMS_Sender_Port;
	
	uint16_t CmdId;
	
	uint16_t StateFlags;
	uint32_t cbData;          // 数据区域的字节长度
	uint32_t ErrorCode;
	uint32_t InvokeId;
	
	ADS_WriteResponse_Typedef Write_Response;        // 回复
} ADS_Write_Request_Receive;         // 接收写入回复




typedef struct 
{
     uint32_t IndexGroup;         // 区
	 uint32_t IndexOffset;        // 地址
	 uint32_t CbLength;           // 数据长度
}ADS_ReadRequest_Typedef;


typedef struct 
{
	 uint32_t Result;
	 uint32_t CbLength;           // 数据长度
	 uint8_t  *Data;              // 数据（由于字节大小不固定，所以设置指针）
}ADS_ReadResponse_Typedef;


typedef struct 
{
  uint8_t  AMS_Target_Net_ID[6];
	uint16_t AMS_Target_Port;
	uint8_t  AMS_Sender_Net_ID[6];
	uint16_t AMS_Sender_Port;
	
	uint16_t CmdId;
	
	uint16_t StateFlags;
	uint32_t cbData;          // 数据区域的字节长度
	uint32_t ErrorCode;
	uint32_t InvokeId;
	
	ADS_ReadRequest_Typedef Read_Request;
} ADS_Read_Request_Send;           // 发送读取命令


typedef struct 
{
  uint8_t  AMS_Target_Net_ID[6];
	uint16_t AMS_Target_Port;
	uint8_t  AMS_Sender_Net_ID[6];
	uint16_t AMS_Sender_Port;
	
	uint16_t CmdId;
	
	uint16_t StateFlags;
	uint32_t cbData;                       // 数据区域的字节长度
	uint32_t ErrorCode;
	uint32_t InvokeId;
	
	ADS_ReadResponse_Typedef Read_Response;// 回复
} ADS_Read_Request_Receive;              // 接收读取回复命令




typedef struct 
{
     uint32_t IndexGroup;         // 区
	 uint32_t IndexOffset;        // 地址
	 uint32_t CbReadLength;       // 数据长度
	 uint32_t CbWriteLength;      // 数据长度
	 uint8_t  *Date;              // 数据
}ADS_ReadWriteRequest_Typedef;


typedef struct 
{
	 uint32_t Result;
	 uint32_t CbLength;           // 数据长度
	 uint8_t  *Data;              // 数据（由于字节大小不固定，所以设置指针）
}ADS_ReadWriteResponse_Typedef;


typedef struct 
{
  uint8_t  AMS_Target_Net_ID[6];
	uint16_t AMS_Target_Port;
	uint8_t  AMS_Sender_Net_ID[6];
	uint16_t AMS_Sender_Port;
	
	uint16_t CmdId;
	
	uint16_t StateFlags;
	uint32_t cbData;          // 数据区域的字节长度
	uint32_t ErrorCode;
	uint32_t InvokeId;
	
	ADS_ReadWriteRequest_Typedef Request;
} ADS_ReadWrite_Request_Send;           // 发送读取命令


typedef struct 
{
    uint8_t  AMS_Target_Net_ID[6];
	uint16_t AMS_Target_Port;
	uint8_t  AMS_Sender_Net_ID[6];
	uint16_t AMS_Sender_Port;
	
	uint16_t CmdId;
	
	uint16_t StateFlags;
	uint32_t cbData;                       // 数据区域的字节长度
	uint32_t ErrorCode;
	uint32_t InvokeId;
	
	ADS_ReadWriteResponse_Typedef Response;// 回复
} ADS_ReadWrite_Request_Receive;           // 接收读取回复命令




typedef struct 
{
    uint8_t  AMS_Target_Net_ID[6];
	uint16_t AMS_Target_Port;
	uint8_t  AMS_Sender_Net_ID[6];
	uint16_t AMS_Sender_Port;
}ADS_Register;

/*
     ADS协议 设置当前的IP 端口 
	 输入参数： target_net_id_port: 目标ip、端口； sender_net_id_port ：本机ip、端口；
	 输出参数： 1成功， 0失败
*/
char ADS_Open(uint8_t *tcp_ip, uint16_t tcp_port);

/*
     ADS协议 设置当前的IP 端口 
	 输入参数： target_net_id_port: 目标ip、端口； sender_net_id_port ：本机ip、端口；
	 输出参数： 1成功， 0失败
*/
char ADS_Close(uint8_t *tcp_ip, uint16_t tcp_port);

/*
     ADS协议 设置当前的IP 端口 
	 输入参数： target_net_id_port: 目标ip、端口； sender_net_id_port ：本机ip、端口；
	 输出参数： 1成功， 0失败
	 
*/
char ADS_SetIdPort(uint8_t *target_net_id_port, uint8_t *sender_net_id_port);

/*
     ADS_Write
	 输入参数： gpoup_index： 区域， index_offset： 地址， dat：数据， lenth 数据长度
	 输出参数： 1成功， 0失败
*/
// 00 00 24 00 00 00 0A 64 AE 1F 01 01 82 FC 0A 64 AD 02 01 01 53 03 03 00 05 00 04 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00
char ADS_Write(ADS_GroupIndex gpoup_index, uint64_t index_offset, uint8_t *dat, uint64_t lenth);

/*
     ADS协议 读取函数
	 输入参数： gpoup_index： 区域， index_offset： 地址， lenth： 数据长度， dat：数据， return_lenth 返回数据长度
	 输出参数： 1成功， 0失败
*/
char ADS_Read(ADS_GroupIndex gpoup_index, uint64_t index_offset, uint64_t lenth, uint8_t *dat, uint16_t *return_lenth);


/*
     ADS协议   ReadWrite
	 输入参数： value_name 
	 输出参数： 1成功， 0失败
*/
char ADS_ReadWrite(uint8_t *value_name, uint8_t *return_dat);

/*
     ADS协议   ReadWrite Read
	 输入参数： value_name 
	 输出参数： 1成功， 0失败
*/
char ADS_ReadWrite_Read(uint8_t *value_name, uint16_t read_lenth, uint8_t *return_dat, uint16_t *return_lenth);


#endif 
