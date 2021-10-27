#include "Isr.h"
#include "communication.h"
/****************************************/
//
//			//-----场中断入口-----//
//
/****************************************/
void PORTA_IRQHandler()
{
    
     PORT_FUNC(A,26,camera_vsync);
}
/****************************************/
//
//	  //-----DMA传输完成中断入口-----//
//
/****************************************/
void DMA0_IRQHandler()
{
    camera_dma();
}
/****************************************/
//
//			//-----超声波中断入口-----//
//
/****************************************/
void PORTE_IRQHandler()
{
    PORT_FUNC(E,11,chaosheng_isr);
}
/****************************************/
//
//			//-----超声波中断服务程序-----//
//
/****************************************/
uint32 Distance = 0;
uint32 Distance_last = 0;
int32 Distance_Err = 0;
uint8 chaosheng_flg = 0;
uint8 Distance_Still_flg = 0;
uint8 Count = 0;
uint32 chaosheng_period = 0;
uint8 temp = 0;

void chaosheng_isr()
{
   	uint32 chaoshengboTime = 0;
        if(Car_State==HOU)
        {
        PIT_TCTRL(PIT1) &= ~ PIT_TCTRL_TEN_MASK;        //禁止PITn定时器（用于清空计数值）
        PIT_TCTRL(PIT1)  = ( 0
                             | PIT_TCTRL_TEN_MASK        //使能 PITn定时器
                             | PIT_TCTRL_TIE_MASK        //开PITn中断
                           );

            if(gpio_get(PTE11)==1 && chaosheng_flg==0)
            {

	       pit_time_start(PIT0);
               chaosheng_flg=1;
           
            }
            else if(gpio_get(PTE11)==0 && chaosheng_flg==1)
            {
                
		chaoshengboTime = pit_time_get_us(PIT0);//(0xFFFFFFFF - PIT_BASE_PTR->CHANNEL[0].CVAL)/50;//50M总线时钟，计算得到时间，单位是微秒
		Distance = chaoshengboTime * 340/10000 + 3;//一秒钟的声音速度假设为340米，由于chaoshengboTime单位是微秒，/10000后得到单位是cm
                pit_close(PIT0);
                if(Distance_Still_flg==0)
                {
                   if(abt32(Distance_last,Distance)>20) 
                     
                   Distance  = Distance_last ;
                }
                Distance_Still_flg = 0;
		if(Distance>200) Distance = 200;
//                if(abt32(Distance,Distance_last)>40)
//		   Distance = Distance_last;
                Distance_Err = Distance-Distance_last;
		Distance_last = Distance;
		chaosheng_flg = 0;
                Distance_Still_flg = 0;
            }
        }
}



void pit1_hander(void)
{
  if(Car_State==HOU)
  {
      gpio_set(PTA6,0);
     Distance_Still_flg = 1;
   }
   else 
   {
      gpio_set(PTA6,1);
     PIT_TCTRL(PIT1) &= ~ PIT_TCTRL_TEN_MASK;        //禁止PITn定时器（用于清空计数值）
    } 
    PIT_Flag_Clear(PIT1); 

}
/****************************************/
//
//			//-----uart0接收中断入口-----//
//
/****************************************/
uint8 uart_get = 0;
void UART0_IRQHandler()
{
    UARTn_e uratn = UART0;

    if(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK)   //接收数据寄存器满
    {
        uart_querychar(UART0,&uart_get);

        UartMsg_Hander(uart_get);//数据处理状态机

    }
}
uint8 uartget = 0;
void UART3_IRQHandler()
{
    UARTn_e uratn = UART3;

    if(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK)   //接收数据寄存器满
    {
        uart_querychar(UART3,&uartget);

        UartMsg_Hander(uartget);//数据处理状态机
        
    }
}
