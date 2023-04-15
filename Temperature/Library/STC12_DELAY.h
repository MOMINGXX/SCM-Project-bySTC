#ifndef __STC12_DELAY_H__
#define __STC12_DELAY_H__

#include <STC12C5A60S2.H>
#include <intrins.h>


#define SYS_CLK 24000000L

#ifndef SYS_CLK 
#define SYS_CLK 11059200L
#endif

//�ӳ�1΢��
void Delay1us();
//�ӳ�5΢��
void Delay5us();
//�ӳ�10΢��
void Delay10us();
//�ӳ�15΢��
void Delay15us();
//�ӳ�50΢��
void Delay50us();	
//�ӳ�100΢��
void Delay100us();	
//�ӳ�1����
void Delay1ms();			
//�ӳ�time����
void Delay(uint16_t time);	

#endif /*__STC12_DELAY_H__*/