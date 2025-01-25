#include <stdint.h>
#include <string.h>
#include "../inc/ads_log.h"


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


/*
     打印数组
     输入参数： hex 数组， num_bytes 数据字节数
     输出参数： 结果
*/
void printf_array(char *front_str, uint8_t *arr, uint16_t lenth)
{
    LOG_RPINTF(front_str);
    for (int i = 0; i < lenth; i++) 
    {
        LOG_RPINTF("0x%02x ", (unsigned char)arr[i]);
    }
    LOG_RPINTF("\n");
}


/*
     将数组转换为整形
     输入参数： hex 数组， num_bytes 数据字节数
     输出参数： 结果
*/
uint64_t Hex_To_Interger(uint8_t *hex, uint16_t num_bytes)
{
    uint64_t num = 0;
    memcpy(&num, hex, num_bytes);
    return num;
}


/*
     查看系统字节序
	 输入参数： 
	 输出参数： 1大端， 0小端
*/
uint8_t check_endianness()
{
    union 
    {
        uint32_t i;
        char c[4];
    } endian_check;

    endian_check.i = 1;

    if (endian_check.c[0] == 1) return 0; // 0 表示小端模式
    else return 1; // 1 表示大端模式
}


/*
     大小端转换
	 输入参数： num 数据， num_bytes 数据字节数
	 输出参数： 结果
*/
uint64_t Endian_Swap(uint64_t num, uint16_t num_bytes)
{
    uint8_t *ptr = (uint8_t *)&num;

    uint16_t i = 0;
    uint16_t j = num_bytes - 1;
    while (i < j) {
        unsigned char temp = ptr[i];
        ptr[i] = ptr[j];
        ptr[j] = temp;
        i++;
        j--;
    }

    return num;
}


/*
     将小端整形拆分字节进数组
	 输入参数： num 数据， num_bytes 数据字节数
	 输出参数： 
*/
void LittleEndianIntergerToHex_ByLittleEndian(uint64_t num, uint16_t num_bytes, uint8_t *hex)
{
    uint64_t endian_comeout = num;
    if(1 == check_endianness())   // 大端
    {
       endian_comeout = Endian_Swap(endian_comeout, num_bytes);  // 小端转大端
    }
    memcpy(hex, &num, num_bytes);
}



/*
     将小端整形转换为大端模式然后拆分字节进数组
	 输入参数： num 数据， num_bytes 数据字节数
	 输出参数： 
*/
void LittleEndianIntergerToHex_ByBigEndian(uint64_t num, uint16_t num_bytes, uint8_t *hex)
{
    uint64_t endian_comeout = num;
    if(0 == check_endianness())   // 小端
    {
       endian_comeout = Endian_Swap(endian_comeout, num_bytes);  // 小端转大端
    }
    memcpy(hex, &num, num_bytes);
}


/*
     将内容为大端的数组依照小端模式转换为整形
	 输入参数： num 数据， num_bytes 数据字节数
	 输出参数： 
*/
void BigEndianHexToInterger_ByLittleEndian(uint8_t *hex,  uint64_t *num, uint16_t num_bytes)
{
    uint64_t tem_num = 0;

    tem_num = Hex_To_Interger(hex, num_bytes); 
    if(1 == check_endianness())   // 大端
    {
       tem_num = Endian_Swap(tem_num, num_bytes);
    }
    
    *num = tem_num;
}

