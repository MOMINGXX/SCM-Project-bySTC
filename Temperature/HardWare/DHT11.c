#include "DHT11.h"

/****
	* @brief	DHT11 ��ʱ80us      			  
	* @param   	��
	* @return   ��  	
	* Sample usage: DHT11_Delay80us();
    */
static void DHT11_Delay80us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 218;
	do
	{
		while (--j);
	} while (--i);
}

/****
	* @brief	DHT11 ��ʱ60us      			  
	* @param   	��
	* @return   ��  	
	* Sample usage: DHT11_Delay60us();
    */
static void DHT11_Delay60us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 98;
	do
	{
		while (--j);
	} while (--i);
}

/****
	* @brief	DHT11 ��ʼ��      			  
	* @param   	��
	* @return   ��  	
	* Sample usage: DHT11_Init();
    */
void DHT11_Init()
{
    uint8_t i;
    DHT11_PIN = 1;
    i = 117;while (--i);        //30us
    DHT11_PIN = 0;
    Delay(20);
    DHT11_PIN = 1;
    i = 117;while (--i);
}

/****
	* @brief	DHT11 ��ȡ����״̬    			  
	* @param   	��
	* @return   0 / 1  	
	* Sample usage:DHT11_Init();
    */
uint8_t DHT11_Read_Bit()
{
    while(DHT11_PIN);           //�ȴ��͵�ƽ ��ʼ��������
    while(!DHT11_PIN);          //�ȴ��ߵ�ƽ
    Delay(60);
    if(DHT11_PIN)
    {
        return 1;
    }
    return 0;
}                                     

/****
	* @brief	DHT11 ��ȡ����   			  
	* @param   	��
	* @return   Byte    ��ȡ������  	
	* Sample usage:DHT11_Read_Byte();
    */
/*
uint8_t DHT11_Read_Byte()
{
    uint8_t i = 0;
    uint8_t Byte = 0x00;
    for(i = 0; i < 8; i++)
    {
        Byte <<= 1;
        Byte |= DHT11_Read_Bit();
    }
}
*/

/****
	* @brief	DHT11 ��ȡ����   			  
	* @param   	��
	* @return   Byte    ��ȡ������  	
	* Sample usage:DHT11_Read_Byte();
    */
uint8_t DHT11_Read_Byte()
{
    uint8_t i = 0;
    uint8_t Byte = 0x00;
    for(i = 0; i < 8; i++)
    {
        while(DHT11_PIN);       //�ȴ��͵�ƽ ��ʼ��������
        while(!DHT11_PIN);
        DHT11_Delay60us();
        Byte <<= 1;
        if(DHT11_PIN == 1)
        {
            Byte += 1;
        }
        while(DHT11_PIN);       //�ȴ��͵�ƽ ��ʼ������һ������
    }
    return Byte;
}

/****
	* @brief	DHT11 ��ȡ��ʪ������   			  
	* @param   	Data    �洢��ȡ����ʪ������ 
	* @return   0 / 1   0>��ȡ�����ݴ���         1    	
	* Sample usage:DHT11_Read_Data(&TempH,&TempL,&HumiH,&HumiL);
    */
void DHT11_Read_Data(uint8_t *TempH,uint8_t *TempL,uint8_t *HumiH,uint8_t *HumiL)
{
	uint8_t i;
	uint8_t Buff[5];
	DHT11_Init();
	if(DHT11_PIN == 0)
	{
		while(DHT11_PIN == 0);    //�ȴ����� 
		//DHT11_Delay80us();		
		for(i=0;i<5;i++)
		{
			Buff[i] = DHT11_Read_Byte();
		}
		//i = 147;while (--i);
		if(Buff[4] == Buff[0] + Buff[1] + Buff[2] + Buff[3])
		{
			*HumiH = Buff[0];
			*HumiL = Buff[1];
			*TempH = Buff[2];
			*TempL = Buff[3];
		}
	}
}
