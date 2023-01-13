#ifndef	__MOTOR_H__
#define __MOTOR_H__

//#include <STC12C5A60S2.H>
#include "Servo.h"
#include "BEEP.h"

#define FORWARD 		("FORWARD")
#define BACK 			("BACK")
#define TURNLEFT		("LEFT")
#define TURNRIGHT		("RIGHT")
#define STOP			("STOP")
#define REDUCESPEED		("REDUCE")
#define ADDSPEED 		("ADD")

//�������������������
sbit LEFT_IN1 =P1^2;
sbit LEFT_IN2 =P1^3;
sbit RIGHT_IN3=P1^4;
sbit RIGHT_IN4=P1^5;

#define LEFT_MOTOR_GO     	 	{LEFT_IN1=1,LEFT_IN2=0;}  	//������ǰת
#define LEFT_MOTOR_BACK   	 	{LEFT_IN1=0,LEFT_IN2=1;} 		//�������ת
#define LEFT_MOTOR_STOP			{LEFT_IN1=0,LEFT_IN2=0;}      //����ͣת                     
#define RIGHT_MOTOR_GO    		{RIGHT_IN3=1,RIGHT_IN4=0;}		//�ҵ����ǰת
#define RIGHT_MOTOR_BACK   		{RIGHT_IN3=0,RIGHT_IN4=1;}		//�ҵ�����ת
#define RIGHT_MOTOR_STOP   		{RIGHT_IN3=0,RIGHT_IN4=0;}      //�ҵ��ͣת 

//����������ʹ�ܶ�����
sbit EN1=P1^6;
sbit EN2=P1^7;

extern uint8_t compare;

//����
void Motor_ReduceSpeed();
//����
void Motor_AddSpeed();
//��ʼ��
void Motor_Init();
//ǰ��
void Motor_ForWard();
//����
void Motor_Back();
//��ת
void Motor_TurnLeft();
//��ת
void Motor_TurnRight();
//ֹͣ
void Motor_Stop();


#endif