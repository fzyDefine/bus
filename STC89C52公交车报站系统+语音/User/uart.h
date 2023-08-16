#ifndef __UART_H_

#include <reg52.h>
#define u8 unsigned char
#define u16 unsigned int

void Uart01_Init(void);
void Uart01_SendByte(u8 _data);
void Uart01_SendString(u8 *str);



#endif // !__UART_H_



