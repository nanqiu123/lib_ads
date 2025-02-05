#ifndef _ADS_TYPEDEF_H_
#define _ADS_TYPEDEF_H_

#include "stdint.h"


/***************************************************************************/
//
//参数定义
//
/***************************************************************************/
typedef enum
{
	ADS_CmdId_ReadDeviceInfo = 0x0001, 
	ADS_CmdId_Read,
	ADS_CmdId_Write, 
	ADS_CmdId_ReadState,
	ADS_CmdId_WriteControl,
	ADS_CmdId_AddDeviceNotification,
    ADS_CmdId_DeleteDeviceNotification,
    ADS_CmdId_DeviceNotification,
	ADS_CmdId_ReadWrite,
}AMS_CmdId_t;

typedef enum
{	
	ADS_StateFlags_REQUEST  = 0x0000,
	ADS_StateFlags_RESPONSE = 0x0001, 
	ADS_StateFlags_COMMAND  = 0x0004, 
}AMS_StateFlags_t;

typedef enum
{						 
	 ADS_GroupIndex_M u = 0x00004020,      
	 ADS_GroupIndex_MX = 0x00004021,    
	 ADS_GroupIndex_I  = 0x0000F020,      
	 ADS_GroupIndex_IX = 0x0000F021, 
	 ADS_GroupIndex_Q  = 0x0000F030, 
	 ADS_GroupIndex_QX = 0X0000f031, 
	 ADS_GroupIndex_HANDLE = 0x0000F003, 
	 ADS_GroupIndex_HANDLE_FOR_VALUE = 0x0000F005,  
	 ADS_GroupIndex_RELEASE_HANDLE = 0x0000F006
} ADS_GroupIndex_t;

typedef enum
{						 
	 ADS_ErrorCode_NoError  = 0x00000000,      
} ADS_ErrorCode_t;


/***************************************************************************/
//
//基础结构定义
//
/***************************************************************************/
#define AMS_TCP_HEADER_BYTES 6
typedef struct 
{
    uint16_t  Reserved;   // 保留 写0
    uint32_t  Command_Lenth;
} AMS_TCP_Header_t;

#define AMS_HEADER_BYTES 32
typedef struct 
{
    uint8_t  AMSNetId_Target[6];
	uint16_t AMSPort_Target;
	uint8_t  AMSNetId_Source[6];
	uint16_t AMSPort_Source;
	
	uint16_t Command_Id;
	
	uint16_t State_Flags;
	uint32_t Data_Length;      // 数据区域的字节长度
	uint32_t Error_Code;
	uint32_t Invoke_Id;
} AMS_Header_t;


/***************************************************************************/
//
// 通讯结构定义
//
/***************************************************************************/
/***************************************************************************/
// 读取设备信息 功能码:ADS_CmdId_ReadDeviceInfo
/***************************************************************************/
#define AMS_READDEVICEINFO_REQUEST_BASE_BYTES  4 + 1 + 1 + 2 + 16 
typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
} ADS_ReadDeviceInfo_Request_t;         

typedef struct 
{
    uint32_t  Result;          // ADS错误码                  
    uint8_t   Major_Version;   // 主版本号
    uint8_t   Minor_Version;   // 次版本号
    uint16_t  Version_Build;   // 构件编号
    uint8_t   Device_Name[16]; // 设备名称
} AMS_ReadDeviceInfo_Receive_Dat_t;


typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_ReadDeviceInfo_Receive_Dat_t Receive;
} ADS_ReadDeviceInfo_Receive_t;  



/***************************************************************************/
// 读取数据 功能码:ADS_CmdId_Read
/***************************************************************************/
#define AMS_READ_REQUEST_BASE_BYTES 4 + 4 + 4
typedef struct 
{
    uint32_t  Index_Group;                  
    uint32_t  Index_Offset;
	uint32_t  Lenth;
} AMS_Read_Request_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_Read_Request_Dat_t Request;
} ADS_Read_Request_t;         


typedef struct 
{
    uint32_t  Result;  // ADS错误码                  
    uint32_t  Lenth;   // 数据长度
	uint8_t   *Data;
} AMS_Read_Receive_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_Read_Receive_Dat_t Receive;
} ADS_Read_Receive_t;     


/***************************************************************************/
// 写数据 功能码:ADS_CmdId_Write
/***************************************************************************/
#define AMS_WRITE_REQUEST_BASE_BYTES 4 + 4 + 4
typedef struct 
{
    uint32_t  Index_Group;                  
    uint32_t  Index_Offset;
	uint32_t  Lenth;
    uint8_t   *Data;
} AMS_Write_Request_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_Write_Request_Dat_t Request;
} ADS_Write_Request_t;         


typedef struct 
{
    uint32_t  Result;  // ADS错误码                  
} AMS_Write_Receive_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_Write_Receive_Dat_t Receive;
} ADS_Write_Receive_t;  


/***************************************************************************/
// 读取状态 功能码:ADS_CmdId_ReadState
/***************************************************************************/
typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
} ADS_ReadState_Request_t;         


typedef struct 
{
    uint32_t  Result;       // ADS错误码 
    uint16_t  ADS_State;    // ADS status (see data type ADSSTATE of the ADS-DLL).
    uint16_t  Device_State; // 设备状态                 
} AMS_ReadState_Receive_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_ReadState_Receive_Dat_t Receive;
} ADS_ReadState_Receive_t; 


/***************************************************************************/
// 写控制字 功能码:ADS_CmdId_WriteControl
/***************************************************************************/
#define AMS_WRITECONTROL_REQUEST_BASE_BYTES 2 + 2 + 4
typedef struct 
{
    uint16_t  ADS_State;          //New ADS status (see data type ADSSTATE of the ADS-DLL).          
    uint16_t  Device_State;
	uint32_t  Lenth;
    uint8_t   *Data;
} AMS_WriteControl_Request_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_WriteControl_Request_Dat_t Request;
} ADS_WriteControl_Request_t;         


typedef struct 
{
    uint32_t  Result;       // ADS错误码                
} AMS_WriteControl_Receive_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_WriteControl_Receive_Dat_t Receive;
} ADS_WriteControl_Receive_t; 


/***************************************************************************/
// 增加设备提示 功能码:ADS_CmdId_AddDeviceNotification
// Increase notifications
// We recommend not to register more than 550 notifications per device. 
// By organizing the data into structures, 
// the payload per notification can be effectively increased.
/***************************************************************************/
#define AMS_ADDDEVICENOTIFICATION_REQUEST_DAT_BASE_BYTES 4 + 4 + 4 +4 + 4 + 4 + 16
typedef struct 
{
    uint32_t  Index_Group;                 
    uint32_t  Index_Offset;
	uint32_t  Lenth;
    uint32_t  Transmission_Mode;//See description of the structure ADSTRANSMODE at the ADS-DLL
    uint32_t  Max_Delay;       //At the latest after this time, the ADS Device Notification is called. The unit is 1ms.
    uint32_t  Cycle_Time;      //The ADS Device Notification is called cyclically. The unit is 1ms.
    uint8_t   Reserved[16];    //Reserved. Set to 0.
} AMS_AddDeviceNotification_Request_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_AddDeviceNotification_Request_Dat_t Request;
} ADS_AddDeviceNotification_Request_t;         


typedef struct 
{
    uint32_t  Result;                 // ADS错误码      
    uint32_t  Notification_Handle;    // Handle of notification         
} AMS_AddDeviceNotification_Receive_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_AddDeviceNotification_Receive_Dat_t Receive;
} ADS_AddDeviceNotification_Receive_t; 


/***************************************************************************/
// 删除设备提示 功能码:ADS_CmdId_DeleteDeviceNotification
/***************************************************************************/
#define AMS_DELETEEVICENOTIFICATION_REQUEST_DAT_BASE_BYTES 4
typedef struct 
{
    uint32_t  Notification_Handle;    // Handle of notification   
} AMS_DeleteDeviceNotification_Request_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_DeleteDeviceNotification_Request_Dat_t Request;
} ADS_DeleteDeviceNotification_Request_t;         


typedef struct 
{
    uint32_t  Result;                 // ADS错误码      
} AMS_DeleteDeviceNotification_Receive_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_DeleteDeviceNotification_Receive_Dat_t Receive;
} ADS_DeleteDeviceNotification_Receive_t; 


/***************************************************************************/
// 设备提示 功能码:ADS_CmdId_DeviceNotification
// Data will carry forward independently from an ADS device to a Client.

/// If the handle has become invalid, a notification without data is sent once as a note
/***************************************************************************/

#define ADS_ADSNOTIFICATIONSAMPLE_BASE_BYTES 4 + 4
typedef struct 
{ 
    uint32_t  Notification_Handle;   // Handle of notification
    uint32_t  Sample_Size;           // Notification handle.
    uint8_t   *Data;      
} Ads_AdsNotificationSample_t;


#define ADS_STAMPHEADER_BASE_BYTES 8 + 4
typedef struct 
{ 
    uint64_t  TimeStamps;    // The timestamp is coded after the Windows FILETIME format. I.e. 
                             // the value contains the number of the nano seconds, which passed since 1.1.1601. 
                             // In addition, the local time change is not considered. 
                             // Thus, the time stamp is present as universal Coordinated time (UTC).

    uint32_t  Samples;       // Number of elements of type AdsNotificationSample.
    Ads_AdsNotificationSample_t *Ads_Notification_Sample;   // Array with elements of type AdsNotificationSample.

} Ads_StampHeader_t;


#define AMS_DEVICENOTIFICATION_REQUEST_DAT_BASE_BYTES 4 + 4
typedef struct 
{ 
    uint32_t  Length;                 // Data length
    uint32_t  Stamps;                 // Number of elements of type AdsStampHeader.
    Ads_StampHeader_t   *Ads_Stamp_Header;        // Array with elements of type AdsStampHeader.
} AMS_DeviceNotification_Request_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_DeviceNotification_Request_Dat_t Request;
} ADS_DeviceNotification_Request_t;         


/***************************************************************************/
// 读写 功能码:ADS_CmdId_ReadWrite
// With ADS ReadWrite data will be written to an ADS device. Additionally, data can be read from the ADS device.
// The data which can be read are addressed by the Index Group and the Index Offset 
/***************************************************************************/
#define AMS_READWRITE_DAT_BASE_BYTES 4 + 4 + 4 + 4 
typedef struct 
{ 
    uint32_t  Index_Group;   
    uint32_t  Index_Offset;   
    uint32_t  Read_Lenth;    
    uint32_t  Write_Lenth;
    uint8_t   *Data;  // Data which are written in the ADS device.
} Ads_ReadWrite_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    Ads_ReadWrite_Dat_t  Request;
} ADS_ReadWrite_Request_t; 


typedef struct 
{
    uint32_t  Result;                 // ADS错误码      
    uint32_t  Lenth;                  // Data length
    uint8_t   *Data;                  // Data which are supplied back.
} AMS_ReadWrite_Receive_Dat_t;

typedef struct 
{
    AMS_TCP_Header_t Ams_Tcp_Header;
	AMS_Header_t     Ams_Header;
    AMS_ReadWrite_Receive_Dat_t Receive;
} ADS_ReadWrite_Receive_t; 


/***************************************************************************/
//
// Ads结构定义
//
/***************************************************************************/
typedef enum 
{
    Ads_Tcp_Disconnected = 0,
    Ads_Tcp_Connected = 1,
} Ads_Tcp_Connect_Cmd_t;

typedef struct 
{
    uint8_t  AMSNetId_Target[6];
	uint16_t AMSPort_Target;
	uint8_t  AMSNetId_Source[6];
	uint16_t AMSPort_Source;
}ADS_Register_t;

typedef struct 
{
    uint8_t  Tcp_Ip[128];
	uint16_t Tcp_Port;
	int16_t  Socket_Handle;  
	int8_t   Connect_State; 
}Tcp_Register_t;

typedef struct
{
    Tcp_Register_t  Tcp_Register;
	ADS_Register_t  Ads_Register;
}Ads_Handle_;                   // ADS句柄

typedef  Ads_Handle_* Ads_Handle_t;  
#endif 
