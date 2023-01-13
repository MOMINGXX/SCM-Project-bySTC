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
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xEA;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;				//������ʱ���ж�
	EA = 1;					//�������ж� 
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
	* @brief      �����ʼ������ʱ��0��ʼ��
	*			  �������������ʼ��
	* @param   	  ��
	* @return     ��       	
	Sample usage:    Motor_Init(); 
    */
void Motor_Init()
{
	Time0_Init();
	
	LEFT_MOTOR_STOP;
	RIGHT_MOTOR_STOP;
}

/****
	@brief      ǰ��
	@param   	��
	@return     ��       	
	Sample usage:    Motor_Ford(); 
****/
void Motor_ForWard()
{
	LEFT_MOTOR_GO;
	RIGHT_MOTOR_GO;
}

/****
	@brief      ����
	@param   	��
	@return     ��       	
	Sample usage:    Motor_Back();        
****/
void Motor_Back()
{
	LEFT_MOTOR_BACK;
	RIGHT_MOTOR_BACK;
}

/****
    *@brief		��ת
    *@param		��
    *@retval	��
	Sample usage:    Motor_Turnleft();  
*****/
void Motor_TurnLeft()
{
	LEFT_MOTOR_BACK;
	RIGHT_MOTOR_GO;
}

/****
    *@brief		��ת
    *@param		��
    *@retval	��
	Sample usage:    Motor_Turnright();  
*****/
void Motor_TurnRight()
{
	LEFT_MOTOR_GO;
	RIGHT_MOTOR_BACK;
}

/****
    *@brief		ֹͣ
    *@param		��
    *@retval	��
	Sample usage:    Motor_Stop();  
*****/
void Motor_Stop()
{
	LEFT_MOTOR_STOP;
	RIGHT_MOTOR_STOP;
}

//��ʱ��0�ж�
void Time0_Routine() interrupt 1
{
	static uint8_t count1=0; //���������־
	static uint8_t count2=0; //���������־
	TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xEA;				//���ö�ʱ��ʼֵ
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
	
	//������
	if(Voice_Count != 0)
	{
		Voice_Count--;
		Beep = 0;
	}
	else
	{
		Beep = 1;
	}
}

	

