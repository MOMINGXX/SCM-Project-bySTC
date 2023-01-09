#include "MOTOR.h"

uint8_t compare=80;

/****
	@brief      ��ʱ����ʼ��		500΢��@11.0592MHz
	@param   	��
	@return     ��       	
	Sample usage:   Time0_Init();
****/
void Time0_Init()
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x33;		//���ö�ʱ��ʼֵ
	TH0 = 0xFE;		//���ö�ʱ��ʼֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;		//������ʱ���ж�
	EA = 1;			//�������ж� 
}

/****
    *@brief		����
    *@param		��
    *@retval	��
*****/
void Motor_AddSpeed()
{
	compare+=10;
}

/****
    *@brief		����
    *@param		��
    *@retval	��
*****/
void Motor_ReduceSpeed()
{
	compare-=10;
}

/****
	@brief    	�������ʱ����ʼ��
	@param   	��
	@return     ��       	
	Sample usage:    Motor_Init(); 
****/
void Motor_Init()
{
	Time0_Init();
	LEFT_IN1=0;
	LEFT_IN2=0;
	
	RIGHT_IN3=0;
	RIGHT_IN4=0;
}

/****
	@brief      ǰ��
	@param   	��
	@return     ��       	
	Sample usage:    Motor_Ford(); 
****/
void Motor_ForWard()
{
	LEFT_IN1=1;
	LEFT_IN2=0;
	
	RIGHT_IN3=1;
	RIGHT_IN4=0;
}

/****
	@brief      ����
	@param   	��
	@return     ��       	
	Sample usage:    Motor_Back();        
****/
void Motor_Back()
{
	LEFT_IN1=0;
	LEFT_IN2=1;
	
	RIGHT_IN3=0;
	RIGHT_IN4=1;
}

/****
    *@brief		��ת
    *@param		��
    *@retval	��
	Sample usage:    Motor_Turnleft();  
*****/
void Motor_TurnLeft()
{
	LEFT_IN1=0;
	LEFT_IN2=1;
	
	RIGHT_IN3=1;
	RIGHT_IN4=0;
}

/****
    *@brief		��ת
    *@param		��
    *@retval	��
	Sample usage:    Motor_Turnright();  
*****/
void Motor_Turnright()
{
	LEFT_IN1=1;
	LEFT_IN2=0;
	
	RIGHT_IN3=0;
	RIGHT_IN4=1;
}

/****
    *@brief		ֹͣ
    *@param		��
    *@retval	��
	Sample usage:    Motor_Stop();  
*****/
void Motor_Stop()
{
	LEFT_IN1=0;
	LEFT_IN2=0;
	
	RIGHT_IN3=0;
	RIGHT_IN4=0;
}

//��ʱ��0�ж�
void Time0_Routine() interrupt 1
{
	static uint8_t count1=0; //���������־
	static uint8_t count2=0; //���������־
	TL0 = 0x33;		//���ö�ʱ��ʼֵ
	TH0 = 0xFE;		//���ö�ʱ��ʼֵ
	//���
	count1++;
	count1 %= 200;
	if(compare > count1)
	{
		EN1=EN2=1;
	}
	else 
	{
		EN1=EN2=0;
	}
		
	//���
	count2++;			//500us ��һ��
	count2 %= 40;		//20ms ����
	if(Servo_PWM > count2)
	{
		Servo=1;
	}
	else 
	{
		Servo=0;
	}
}

	

