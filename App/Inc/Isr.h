#ifndef Isr_h
#define Isr_h
#include "include.h"




//��������
extern uint32 Distance;
extern uint32 Distance_last;
extern uint8 Distance_Still_flg;
extern uint8 uart_get;

//��������
void PORTA_IRQHandler();
void PORTE_IRQHandler();
void DMA0_IRQHandler();
void chaosheng_isr();
void UART0_IRQHandler();
void pit1_hander(void);
void UART3_IRQHandler();






#endif