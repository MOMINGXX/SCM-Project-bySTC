#include "UART.h"

RXPACKAGE_typedef RXPACKAGE;
bit Flag1 = 0; // ��־λ

uint8_t DAT2;				// ��Ž��յ��ַ�
uint8_t RX2_BUFF[DATA_MAX]; // ���յ�����	������
uint8_t RX2_DAT[DATA_MAX];	// ��Ž��յ�����
uint8_t RX2_COUNT = 0;		// ���ռ���
bit Flag2 = 0;				// ��־λ

/****
	@brief      ���ڳ�ʼ��
	@param   	Uart_n			���ں�  USART_1,USART_2
	@param		GPIORX_Pin		����I/O��	P30 P12 P42
	@param		GPIOTX_Pin		����I/O��	P31 P13 P43
	@param		baud			������	115200 57600 9600 4800 2400
	@param		Tim_n			�����ʷ�����
	@return     ��
	Sample usage:  Uart_Init(UART_1,GPIORX_P30,GPIOTX_P31,9600,Tim_1);
	@note    ���貨���ʼӱ� ��	#define SMOD 0	-->  #define SMOD 1
****/
void Uart_Init(UART_NAME Uart_n, GPIO_PIN GPIORX_Pin, GPIO_PIN GPIOTX_Pin, uint16_t baud, UART_TIM Tim_n)
{
	switch (Uart_n)
	{
	case UART_1:
	{
		SCON = 0x50; // 8λ����,�ɱ䲨����
#if SMOD == 0
		PCON &= 0x7F; // �����ʲ�����
#elif SMOD == 1
		PCON |= 0x80;							// ʹ�ܲ����ʱ���λSMOD
#endif
		if (TIM_1 == Tim_n)
		{
			AUXR |= 0x40; // ��ʱ��ʱ��1Tģʽ
			AUXR &= 0xFE; // ����1ѡ��ʱ��1Ϊ�����ʷ�����
			TMOD &= 0x0F; // ���ö�ʱ��ģʽ
			TMOD |= 0x20; // ���ö�ʱ��ģʽ
#if SMOD == 1
			TL1 = TH1 = -(2 * SYS_CLK / 32 / baud); // ���ö�ʱ����ʼֵ������ֵ
#elif SMOD == 0
			TL1 = TH1 = -(SYS_CLK / 32 / baud); // ���ö�ʱ����ʼֵ������ֵ
#endif

#ifndef OPEN_EA
			ET1 = 0; // ��ֹ��ʱ���ж�
			TR1 = 1; // ��ʱ��1��ʼ��ʱ
#endif
		}
		else if (TIM_BRT == Tim_n)
		{
#if SMOD == 1
			BRT = -(2 * SYS_CLK / 32 / baud); // ���ö�ʱ����ֵ
#elif SMOD == 0
			BRT = -(SYS_CLK / 32 / baud);		// ���ö�ʱ����ֵ
#endif
			AUXR |= 0x04; // ��ʱ��ʱ��1Tģʽ
			AUXR |= 0x01; // ����1ʹ�ö��������ʷ�����Ϊ�����ʷ�����
			AUXR |= 0x10; // �������������ʷ�����
		}
		if (GPIORX_P30 == GPIORX_Pin && GPIOTX_P31 == GPIOTX_Pin)
		{
			// P30˫��IO��
			P3M1 &= ~0x01;
			P3M0 &= ~0x01;
			// P31˫��IO��
			P3M1 &= ~0x02;
			P3M0 &= ~0x02;
		}
		break;
	}
	case UART_2:
	{
#if SMOD == 1
		AUXR |= 0x08;					  // ʹ�ܲ����ʱ���λS2SMOD
		BRT = -(2 * SYS_CLK / 32 / baud); // ���ö�ʱ����ֵ
#elif SMOD == 0
		AUXR &= 0xF7;							// �����ʲ�����
		BRT = -(SYS_CLK / 32 / baud);			// ���ö�ʱ����ֵ
#endif
		S2CON = 0x50; // 8λ����,�ɱ䲨����
		AUXR |= 0x04; // ��ʱ��ʱ��1Tģʽ
		AUXR |= 0x10; // �������������ʷ�����
		if (GPIORX_P12 == GPIORX_Pin && GPIOTX_P13 == GPIOTX_Pin)
		{
			// P12˫��IO��
			P1M1 &= ~0x40;
			P1M0 &= ~0x40;

			// P13˫��IO��
			P1M1 &= ~0x80;
			P1M0 &= ~0x80;
			AUXR1 &= ~0x10;
		}
		else if (GPIORX_P42 == GPIORX_Pin && GPIOTX_P43 == GPIOTX_Pin)
		{
			// P42˫��IO��
			P4M1 &= ~0x40;
			P4M0 &= ~0x40;

			// P43˫��IO��
			P4M1 &= ~0x80;
			P4M0 &= ~0x80;
			AUXR1 |= 0x10;
		}
		break;
	}
	}
}

/****
	@brief      ���ڷ���һ���ֽ�
	@param   	uart_n          ���ں�  USART_1,USART_2
	@param    	Byte  			Ҫ���͵��ֽ�
	@return     ��
	Sample usage:    Uart_SendByte(UART_1,'p');
****/
void Uart_SendByte(UART_NAME Uart_n, uint8_t Byte)
{
	switch (Uart_n)
	{
	case UART_1:
	{
		SBUF = Byte;
		while (!UART1_GET_TX_FLAG);
		UART1_CLEAR_TX_FLAG;
	}
	break;
	case UART_2:
	{
		S2BUF = Byte;
		while (UART2_GET_TX_FLAG == 0);
		UART2_CLEAR_TX_FLAG;
	}
	break;
	}
}

/****
	@brief      ���ڷ���һ���ַ���
	@param   	uart_n          ���ں�  USART_1,USART_2
	@param   	String			Ҫ���͵��ַ���
	@return     ��
	Sample usage:     Uart_SendString(UART_1,"ABCD");
****/
void Uart_SendString(UART_NAME Uart_n, uint8_t *String)
{
	while (*String != '\0')
	{
		Uart_SendByte(Uart_n, *String++);
	}
}

/****
	@brief      ���ڷ�������
	@param   	uart_n          ���ں�  USART_1,USART_2
	@param   	Buff			Ҫ���͵�����
	@param   	Len				���鳤��
	@return     ��
	Sample usage:     Uart_SendString(UART_1,arr,sizeof(arr)/sizeof(arr[0]));
****/
void Uart_SendBuff(UART_NAME Uart_n, uint8_t *Buff, uint16_t Len)
{
	while (Len--)
	{
		Uart_SendByte(Uart_n, *Buff++);
	}
}

/****
	@brief      printf��ӡ
	@param   	c
	@return     c
	Sample usage:  printf("Hello\n");
****/
#if (PRINTF_SELECT == 1)
int putchar(int c)
{
	if (c == '\n')
	{
		Uart_SendByte(UART_1, 0x0D);
	}
	Uart_SendByte(UART_1, c);
	return c;
}

#elif (PRINTF_SELECT == 2)
char putchar(char c)
{
	if (c == '\n')
	{
		Uart_SendByte(UART_1, 0x0D);
	}
	Uart_SendByte(UART_1, c);
	return c;
}
#endif

/*
//������
#if (PRINTF_SELECT == 1)
char putchar(char c)
{
	Uart_SendByte(UART_1,c);
	return c;
}

#elif (PRINTF_SELECT == 2)
char putchar(char c)
{
	Uart_SendByte(UART_1,c);
	return c;
}
#endif
*/

// ����1�жϽ�������
#if UART_ROUTINE_SELECT == 1
void Uart1_Routine() interrupt 4
{
	static uint8_t RX_Count = 0;
	uint8_t RX_Temp = 0;
	if (UART1_GET_RX_FLAG)
	{
		UART1_CLEAR_RX_FLAG;
		RX_Temp = SBUF;
		if (0 == RX_Count)
		{
			if (0xA5 == RX_Temp)
			{
				RX_Count++;
			}
		}
		else if (1 == RX_Count)
		{
			if (0x6A == RX_Temp)
			{
				RX_Count++;
				RXPACKAGE.RX_Head = 0xA56A;
			}
			else
			{
				RX_Count = 0;
			}
		}
		else if (2 == RX_Count)
		{
			RX_Count++;
			RXPACKAGE.RX_CMD = RX_Temp;
		}
		else if (3 == RX_Count)
		{
			RX_Count++;
			if (RX_Temp <= PACKAGE_MAXSIZE)
			{
				RXPACKAGE.DATA_Len = RX_Temp;
			}
			else
			{
				RX_Count = 0;
				RXPACKAGE.DATA_Len = 0;
			}
		}
		else if (RX_Count < RXPACKAGE.DATA_Len - 2)
		{
			RXPACKAGE.RX_Data[RX_Count - 4] = RX_Temp;
			RX_Count++;
		}
		else if (RX_Count == RXPACKAGE.DATA_Len - 2)
		{
			RXPACKAGE.CRC16 = RX_Temp;
			RX_Count++;
		}
		else if (RX_Count == RXPACKAGE.DATA_Len - 1)
		{
			RXPACKAGE.CRC16 = RXPACKAGE.CRC16 | RX_Temp << 8;
			RX_Count = 0;
		}
		else
		{
			RX_Count = 0;
			RXPACKAGE.DATA_Len = 0;
		}
		Flag1 = 1;
	}
}

// ����2�жϽ�������
#elif UART_ROUTINE_SELECT == 2
void Uart1_Routine() interrupt 8
{
	static uint8_t i = 0;
	if (UART2_GET_RX_FLAG)
	{
		UART2_CLEAR_RX_FLAG;
		DAT2 = S2BUF;
		if (DAT2 != '#') //'#'������־
		{
			RX2_BUFF[RX2_COUNT++] = DAT2++;
		}
		else
		{
			for (i = 0; i < RX2_COUNT; i++)
			{
				RX2_DAT[i] = RX2_BUFF[i];
			}
			RX2_COUNT = 0;
			Flag2 = 1;
		}
	}
}
#endif
