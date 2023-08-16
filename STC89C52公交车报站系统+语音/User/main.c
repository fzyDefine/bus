/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net

实验名称：LCD12864液晶显示实验（带字库）
接线说明：	
实验现象：下载程序后，LCD12864上显示汉字字符信息
注意事项：																				  
***************************************************************************************/
#include "public.h"
#include "lcd12864.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/

#define TOTAL_STATION 12
#define STR_MAXLENGTH 17
sbit KEY_PIN  = P2^3;

char code station_buffer[TOTAL_STATION][STR_MAXLENGTH] =
{
	"袁州工业区","井竹名爵","晨阳绿城","经开区物流中心",
	"春风路口东","市环保局","高仕名居","正荣丽景山庄",
	"袁山公园","高士北路","高市路","街心花园"
};

void LCD_ShowConnect(unsigned char cur_station)
{
	char now_index = cur_station % TOTAL_STATION;
	char next_index = (now_index + 1) % TOTAL_STATION;
	
	lcd12864_show_string(0,0,"当前站:");//第1行字符串显示
	lcd12864_show_string(0,1,station_buffer[now_index]);//第2行字符串显示
	lcd12864_show_string(0,2,"下一站");//第3行字符串显示
	lcd12864_show_string(0,3,station_buffer[next_index]);//第4行字符串显示

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

	lcd12864_init();//LCD12864初始化

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
//			lcd12864_show_string(0,0,temp_buffer);//第1行字符串显示
		}
		
		
		LCD_ShowConnect(cur_station);
	}	
}

void Uart01_Routine() interrupt 4
{
	u8 uart_data; //串口收到的数据
    if(RI == 1)
    {
        RI = 0;
        uart_data = SBUF;

    }
}