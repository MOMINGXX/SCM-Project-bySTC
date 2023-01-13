#include "ULTRASONIC.h"

uint16_t Distance = 0;

/****
	* @brief	��ʱ��1��ʼ��      //11.0592MHz		  
	* @param   	��
	* @return   ��    	
	* Sample usage:Timer0_Init();
	* @note 
    */
void Timer1_Init()		
{
	AUXR |= 0x40;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;			//���ö�ʱ��ģʽ
	TMOD |= 0x10;			//���ö�ʱ��ģʽ
	TL1 = 0;				//���ö�ʱ��ʼֵ
	TH1 = 0;				//���ö�ʱ��ʼֵ
	TF1 = 0;				//���TF1��־
	TR1 = 1;				//��ʱ��1��ʼ��ʱ
}

/****
	* @brief	��������ʼ��      			  
	* @param   	��
	* @return   ��    	
	* Sample usage:Ultrasonic_Init();
	* @note 
    */
void Ultrasonic_Init()
{
	Trig = 0;
	Echo = 0;
	Timer1_Init();	
}

/****
	* @brief	����������     			  
	* @param   	��
	* @return   ��    	
	* Sample usage:Ultrasonic_Start();
	* @note 
    */
static void Ultrasonic_Start()
{
	Trig = 0;
	_nop_();
	Trig = 1;
	Delay10us();
	Trig = 0;
}

/****
	* @brief	�������������		  
	* @param   	��
	* @return   ��    	
	* Sample usage:Ultrasonic_GetDistance();
    */
uint16_t Ultrasonic_GetDistance()
{
	uint16_t Time = 0;
	
	Ultrasonic_Start();
	Echo = 1;
	while(!Echo);		//�ȴ��͵�ƽ����
	TR1 = 1;
	while(Echo);		//�ȴ��ߵ�ƽ����
	TR1 = 0;
	
	Time = TH1*256+TL1;
	TH1=0;
	TL1=0;
	//Time = Time * (12/24);
	
	Distance = Time *1.7/100;		//�������  mm
	return Distance;
}

