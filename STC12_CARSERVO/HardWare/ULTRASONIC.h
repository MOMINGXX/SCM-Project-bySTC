#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include "STC12_DELAY.h"

sbit Trig = P3^4;         //������ģ�鴥����
sbit Echo = P3^5;         //������ģ������

//extern uint16_t Distance;

void Ultrasonic_Init();
uint16_t Ultrasonic_GetDistance();

#endif /*__ULTRASONIC_H__*/