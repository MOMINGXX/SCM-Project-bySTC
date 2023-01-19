#include "STC12_DELAY.h"

#if (SYS_CLK == 24000000)

/****
	@brief      �ӳ�1΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay1us(); �ӳ�1us
****/
void Delay1us()		
{
    uint8_t i;
	i = 3;
	while (--i);
}

/****
	@brief      �ӳ�5΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay5us(); �ӳ�5us
****/
void Delay5us()	
{
	uint8_t i;
	i = 27;
	while (--i);
}

/****
	@brief      �ӳ�10΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay10us(); �ӳ�10us
****/
void Delay10us()	
{
	uint8_t i;
	i = 57;
	while (--i);
}

/****
	@brief      �ӳ�15΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay15us(); �ӳ�15us
****/
void Delay15us()		
{
	uint8_t i;
	_nop_();
	_nop_();
	i = 38;
	while (--i);
}

/****
	@brief      �ӳ�50΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay50us(); �ӳ�50us
****/
void Delay50us()		
{
	uint8_t i;
	uint8_t j;
    _nop_();
    _nop_();
	i = 2;
	j = 38;
	do
	{
		while (--j);
	} while (--i);
}

/****
	@brief      �ӳ�100΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay100us(); �ӳ�100us
****/
void Delay100us()	
{
	uint8_t i;
	uint8_t j;
    _nop_();
    _nop_();
	i = 3;
	j = 81;
	do
	{
		while (--j);
	} while (--i);
}

/****
	@brief      �ӳ�1����
	@param		��	
	@return     ��        	
	Sample usage:  Delay1ms(); �ӳ�1ms
****/
void Delay1ms()
{
	uint8_t i;
	uint8_t j;
    _nop_();
    _nop_();
	i = 24;
	j = 84;
	do
	{
		while (--j);
	} while (--i);
}

#elif (SYS_CLK == 12000000)		//12MHz

/****
	@brief      �ӳ�1΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay1us(); �ӳ�1us
****/
void Delay1us()		//@12.000
{
	_nop_();
    _nop_();
}

/****
	@brief      �ӳ�5΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay5us(); �ӳ�5us
****/
void Delay5us()		//@12.000
{
	uint8_t i;
	i = 12;
	while (--i);
}

/****
	@brief      �ӳ�10΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay10us(); �ӳ�10us
****/
void Delay10us()		
{
	uint8_t i;
	i = 27;
	while (--i);
}

/****
	@brief      �ӳ�15΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay15us(); �ӳ�15us
****/
void Delay15us()		
{
	uint8_t i;
	_nop_();
	_nop_();
	i = 38;
	while (--i);
}

/****
	@brief      �ӳ�50΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay100us(); �ӳ�50us
****/
void Delay50us()		
{
	uint8_t i;
	uint8_t j;
    _nop_();
    _nop_();
	i = 1;
	j = 145;
	do
	{
		while (--j);
	}while (--i);
}

/****
	@brief      �ӳ�100΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay100us(); �ӳ�100us
****/
void Delay100us()		
{
	uint8_t i;
	uint8_t j;
    _nop_();
    _nop_();
	i = 2;
	j = 38;
	do
	{
		while (--j);
	} while (--i);
}

/****
	@brief      �ӳ�1����
	@param		��	
	@return     ��        	
	Sample usage:  Delay1ms(); �ӳ�1ms
****/
void Delay1ms()	
{
	uint8_t i;
	uint8_t j;
    _nop_();
    _nop_();
	i = 12;
	j = 168;
	do
	{
		while (--j);
	} while (--i);
}

#else //11059200MHz

/****
	@brief      �ӳ�1΢��
	@param		��	
	@return     ��        	
	Sample usage: Delay1us(); �ӳ�1us
****/
void Delay1us()		
{
	_nop_();
}

/****
	@brief      �ӳ�5΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay5us(); �ӳ�5us
****/
void Delay5us()	
{
	uint8_t i;
	_nop_();
	_nop_();
    _nop_();
	i = 10;
	while (--i);
}

/****
	@brief      �ӳ�10΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay10us(); �ӳ�10us
****/
void Delay10us()		
{
	uint8_t i;
	_nop_();
	_nop_();
    _nop_();
	i = 24;
	while (--i);
}

/****
	@brief      �ӳ�15΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay15us(); �ӳ�15us
****/
void Delay15us()		
{
	uint8_t i;
	_nop_();
	_nop_();
	i = 38;
	while (--i);
}

/****
	@brief      �ӳ�50΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay100us(); �ӳ�50us
****/
void Delay50us()	
{
	uint8_t i;
	uint8_t j;
    _nop_();
    _nop_();
    _nop_();
	i = 1;
	j = 133;
	do
	{
		while (--j);
	} while (--i);
}

/****
	@brief      �ӳ�100΢��
	@param		��	
	@return     ��        	
	Sample usage:  Delay100us(); �ӳ�100us
****/
void Delay100us()		
{
	uint8_t i;
	uint8_t j;
	i = 2;
	j = 15;
	do
	{
		while (--j);
	}while (--i);
}

/****
	@brief      �ӳ�1����
	@param		��	
	@return     ��        	
	Sample usage:  Delay1ms(); �ӳ�1ms
****/
void Delay1ms()
{
	uint8_t i;
	uint8_t j;
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	}while(--i);
}

#endif

/****
	@brief      �ӳ�time����
	@param		time	�ӳ�ʱ��(1-65535)	
	@return     ��        	
	Sample usage:  Delay(1000); �ӳ�1s
****/
void Delay(uint16_t time)
{
	if(time < 1)
	{
		time = 1;
	}	
	do 
	{ 
		Delay1ms();
	}while (--time);
}