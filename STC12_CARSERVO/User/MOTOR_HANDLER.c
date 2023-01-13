#include "MOTOR_HANDLER.h"

uint8_t Auto_Hand_Mode_Flag=1;	//�Զ��ֶ�ģʽ�л���־(Ĭ������ģʽ)

uint16_t Distance_Middle = 0;	//�м����
uint16_t Distance_Left = 0;		//������
uint16_t Distance_Right = 0;	//�Ҳ����

/****
	* @brief	����...ģʽ		������������ģ��ʹ��
	* @param   	��
	* @return   ��    	
	* Sample usage:MOTOR_Blue_Mode();
	* @note 
    */
void MOTOR_Blue_Mode()
{
	if(Flag1 == 1)
	{
		if(strstr(RX1_DAT,FORWARD) != NULL)			//���յ������бȽ�
		{
			Motor_ForWard();		//ǰ��
		}
		else if(strstr(RX1_DAT,BACK) != NULL)
		{
			Motor_Back();			//����
		}
		else if(strstr(RX1_DAT,TURNLEFT) != NULL)
		{
			Motor_TurnLeft(); 		//��ת
		}
		else if(strstr(RX1_DAT,TURNRIGHT) != NULL)
		{
			Motor_TurnRight(); 		//��ת
		}
		else if(strstr(RX1_DAT,STOP) != NULL)
		{
			Motor_Stop();			//ֹͣ
		}
		else if(strstr(RX1_DAT,REDUCESPEED	) != NULL)
		{
			Motor_ReduceSpeed();	//����		ÿ�� ��10 
		}
		else if(strstr(RX1_DAT,ADDSPEED ) != NULL)
		{
			Motor_AddSpeed(); 		//����		ÿ�� ��10 
		}
		Flag1=0;						//���ձ�־����
		Uart_SendString(UART_1,RX1_DAT); 
	}
}

/****
	* @brief	����ģʽ
	* @param   	��
	* @return   ��    	
	* Sample usage:Motor_Ultrasonic_Mode();
	* @note 
    */
void Motor_Ultrasonic_Mode()
{
	Servo_PWM = 3;			//������ת���м�
	Delay1ms();
	Distance_Middle = Ultrasonic_GetDistance();			//����Ҳ����
	Delay1ms();
	if(Distance_Middle <= 200)
	{
		Voice_Count = 200;		//����������

		Motor_Stop();			//ֹͣ

		Servo_PWM = 1;		//������ת���Ҳ�
		Delay(1000);
		Distance_Right = Ultrasonic_GetDistance();		//����Ҳ����
		Delay1ms();

		Servo_PWM = 5;		//������ת�����
		Delay(1600);
		Distance_Left = Ultrasonic_GetDistance();		//���������
		Delay1ms();
	}
	if(Distance_Middle > 300)		//ǰ���������30cm  ǰ��
	{
		Motor_ForWard();
	}
	else if(Distance_Right >= Distance_Left && Distance_Right > 300)	
	{
		//���Ҿ����������� ���Ҵ���30cmʱ  ��תһ��ʱ��ͣ��
		Motor_TurnRight();
		Delay(1000);
		Motor_Stop();
	}
	else if(Distance_Right <= Distance_Left && Distance_Left > 300)		
	{
		//�����������Ҿ��� ���Ҵ���30cmʱ  ��תһ��ʱ��ͣ��
		Motor_TurnLeft();
		Delay(1000);
		Motor_Stop();
	}
	//printf("Distance:%d\r\n",Distance_Middle);			//��ӡ�¾���
}

/****
	* @brief	����ģʽ�л� -- ����  ����  
	* @param   	��
	* @return   ��    	
	* Sample usage:Auto_Hand_Mode();
	* @note 
    */
void Auto_Hand_Mode()
{
	switch(Auto_Hand_Mode_Flag)
	{
		case Ultrasonic_Mode:
			Motor_Ultrasonic_Mode();		//����
		break;
		case Blue_Mode:
			MOTOR_Blue_Mode();				//����
		break;
		default:							//�������ֻ�� 0 / 1 ���� ����ִ�и����  ���Բ�д
			printf("Select Err\n");
		break;
	}
}

/****
	* @brief	Into �жϺ���  -- ��ⰴ�� 
	* @param   	��
	* @return   ��  
	* @note 	���ڰ����� P3.2 �������ж�  Ҳ����дһ��������⺯��
    */
void Int0() interrupt 0
{
	if(Key == 0)
	{
		Delay(20);
		if(Key == 0)
		{
			if(Auto_Hand_Mode_Flag)		
			{
				Auto_Hand_Mode_Flag = 0;
			}
			else 
			{
				Auto_Hand_Mode_Flag = 1;
			}
		}
		while(!Key);
	}
}