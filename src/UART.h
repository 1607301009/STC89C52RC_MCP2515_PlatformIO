#ifndef __UART_H
#define __UART_H

void UART_init(void);
void UART_send_str(uint8 d);
// ���ڴ˴��������ж��쳣
void uart(void) __interrupt 4;
int putchar(int c);

#endif