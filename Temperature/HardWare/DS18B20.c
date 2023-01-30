#include "DS18B20.h"

/****
	* @brief	DS18B20 ��ʱ550us     			  
	* @param   	��
	* @return   ��  	
	* Sample usage:DS18B20_Delay550us();
    */
void DS18B20_Delay550us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 13;
	j = 211;
	do
	{
		while (--j);
	} while (--i);
}

/****
	* @brief	DS18B20 ��ʼ��    			  
	* @param   	��
	* @return   ��  	
	* Sample usage:DS18B20_Init();
    */
void DS18B20_Init()
{
    DS18B20_PIN = 1;
    DS18B20_PIN = 0;
    DS18B20_Delay550us();
    DS18B20_PIN = 1;
  	DS18B20_Delay550us();
}

/****
	* @brief	DS18B20 дһλ����    			  
	* @param   	Bit		Ҫд��һλ����   	
	* @return   ��  	
	* Sample usage:DS18B20_WriteBit(0x01);
    */
void DS18B20_WriteBit(uint8_t Bit)
{
	DS18B20_PIN = 0;
	Delay10us();
	DS18B20_PIN = Bit;
	Delay50us();
    DS18B20_PIN = 1;
}

/****
	* @brief	DS18B20 дһ���ֽ�����    			  
	* @param   	Bit		Ҫд���ֽ�����   	
	* @return   ��  	
	* Sample usage:DS18B20_WriteByte( Byte);
    */
void DS18B20_WriteByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		DS18B20_WriteBit(Byte&(0x01<<i));
	}
}

/****
	* @brief	DS18B20 ��һλ����    			  
	* @param   	��		   	
	* @return   Bit  	����������
	* Sample usage:DS18B20_ReadBit();
    */
uint8_t DS18B20_ReadBit()
{
	uint8_t Bit;
	DS18B20_PIN = 0;
	Delay5us();
	DS18B20_PIN = 1;
	Delay5us();
	Bit = DS18B20_PIN;
	Delay50us();
	return Bit;	
}

/****
	* @brief	DS18B20 ��һ�ֽ�����    			  
	* @param   	��		   	
	* @return   Byte  	�������ֽ�����
	* Sample usage:DS18B20_ReadBit();
    */
uint8_t DS18B20_ReadByte()
{
	uint8_t i;
	uint8_t Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(DS18B20_ReadBit())
		{
			Byte|=(0x01<<i);
		}
	}
	return Byte;
}

/****
	* @brief	DS18B20 �¶�ת��  			  
	* @param   	��		   	
	* @return   ��
	* Sample usage:DS18B20_ConvertT();
    */
void DS18B20_ConvertT()
{
	DS18B20_Init();
	DS18B20_WriteByte(DS18B20_SKIP_ROM);
	DS18B20_WriteByte(DS18B20_CONVERT_T);
}

/****
	* @brief	DS18B20 ��ȡ�¶�����			  
	* @param   	��		   	
	* @return   T	�������¶�����
	* Sample usage:DS18B20_ReadT();
    */
float DS18B20_ReadT()
{
	uint8_t TLSB,TMSB;
	int Temp;
	float T;
	DS18B20_Init();
	DS18B20_WriteByte(DS18B20_SKIP_ROM);
	DS18B20_WriteByte(DS18B20_READ_SCRATCHPAD);
	TLSB=DS18B20_ReadByte();
	TMSB=DS18B20_ReadByte();
	Temp=(TMSB<<8)|TLSB;
	T=Temp/16.0;
	return T;
}