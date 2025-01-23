#ifndef __ADS_TOOLS_H__
#define __ADS_TOOLS_H__

#include <stdint.h>
/*
     打印数组
     输入参数： hex 数组， num_bytes 数据字节数
     输出参数： 结果
*/
void printf_array(char *front_str, uint8_t *arr, uint16_t lenth);


// 反转数组的函数
void reverseArray(uint8_t arr[], int size);


/*
     将数组转换为整形
     输入参数： hex 数组， num_bytes 数据字节数
     输出参数： 结果
*/
uint64_t Hex_To_Interger(uint8_t *hex, uint16_t num_bytes);


/*
     查看系统字节序
	 输入参数： 
	 输出参数： 1大端， 0小端
*/
uint8_t check_endianness();


/*
     大小端转换
	 输入参数： num 数据， num_bytes 数据字节数
	 输出参数： 结果
*/
uint64_t Endian_Swap(uint64_t num, uint16_t num_bytes);


/*
     将小端整形拆分字节进数组
	 输入参数： num 数据， num_bytes 数据字节数
	 输出参数： 
*/
void LittleEndianIntergerToHex_ByLittleEndian(uint64_t num, uint16_t num_bytes, uint8_t *hex);


/*
     将整形拆分转换为大端模式然后拆分字节进数组
	 输入参数： num 数据， num_bytes 数据字节数
	 输出参数： 
*/
void LittleEndianIntergerToHex_ByBigEndian(uint64_t num, uint16_t num_bytes, uint8_t *hex);


/*
     将内容为大端的数组依照小端模式转换为整形
	 输入参数： num 数据， num_bytes 数据字节数
	 输出参数： 
*/
void BigEndianHexToInterger_ByLittleEndian(uint8_t *hex,  uint64_t *num, uint16_t num_bytes);

#endif