#include "uart.h"
bit busy;

void Uart01_Init(void)		//9600bps@12MHz
{
	TMOD|=0X20;	//设置计数器工作方式2
	SCON=0X50;	//设置为工作方式1
	PCON=0X80;	//波特率加倍
	TH1=0XFA;	//计数器初始值设置
	TL1=0XFA;
	ES=1;		//打开接收中断
	EA=1;		//打开总中断
	TR1=1;		//打开计数器	

	EA=1;
	ES=1;
}

void Uart01_SendByte(u8 _data)
{
    SBUF = _data;
    while(TI == 0);
    TI = 0;
}

void Uart01_SendString(u8 *str)
{
	while(*str !='\0')		
		Uart01_SendByte(*str++);
}

