/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net

ʵ�����ƣ�LCD12864Һ����ʾʵ�飨���ֿ⣩
����˵����	
ʵ���������س����LCD12864����ʾ�����ַ���Ϣ
ע�����																				  
***************************************************************************************/
#include "public.h"
#include "lcd12864.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/

#define TOTAL_STATION 12
#define STR_MAXLENGTH 17
sbit KEY_PIN  = P2^3;

char code station_buffer[TOTAL_STATION][STR_MAXLENGTH] =
{
	"Ԭ�ݹ�ҵ��","��������","�����̳�","��������������",
	"����·�ڶ�","�л�����","��������","��������ɽׯ",
	"Ԭɽ��԰","��ʿ��·","����·","���Ļ�԰"
};

void LCD_ShowConnect(unsigned char cur_station)
{
	char now_index = cur_station % TOTAL_STATION;
	char next_index = (now_index + 1) % TOTAL_STATION;
	
	lcd12864_show_string(0,0,"��ǰվ:");//��1���ַ�����ʾ
	lcd12864_show_string(0,1,station_buffer[now_index]);//��2���ַ�����ʾ
	lcd12864_show_string(0,2,"��һվ");//��3���ַ�����ʾ
	lcd12864_show_string(0,3,station_buffer[next_index]);//��4���ַ�����ʾ

}

void Delay15ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 27;
	j = 226;
	do
	{
		while (--j);
	} while (--i);
}

unsigned char key_scan()
{
	unsigned char key_v = 0;
	if(KEY_PIN == 0)
	{
		Delay15ms();
		if(KEY_PIN == 0)
		{
			key_v = 1;
		}
		while(!KEY_PIN);
	}

	return key_v;
}

void main()
{	
	unsigned char key_num = 0;
	int cur_station = 0;
	unsigned char i = 0;
	u8 temp_buffer[30] = "";

	lcd12864_init();//LCD12864��ʼ��

	Uart01_Init();


	lcd12864_clear();
	Uart01_SendString("A8:02/1*WAV");		
	while(1)
	{	
		key_num = key_scan();
		if(key_num == 1)
		{

		
			lcd12864_clear();
			cur_station++;


			if(cur_station >= TOTAL_STATION)
				cur_station = 0;

			memset(temp_buffer,0,30);
			sprintf(temp_buffer,"A8:02/%d*WAV",cur_station % TOTAL_STATION+1);
			Uart01_SendString(temp_buffer);
//			lcd12864_show_string(0,0,temp_buffer);//��1���ַ�����ʾ
		}
		
		
		LCD_ShowConnect(cur_station);
	}	
}

void Uart01_Routine() interrupt 4
{
	u8 uart_data; //�����յ�������
    if(RI == 1)
    {
        RI = 0;
        uart_data = SBUF;

    }
}