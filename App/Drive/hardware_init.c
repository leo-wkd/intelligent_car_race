#include "Drive.h"
#include "stdio.h"
//函数声明
void adc();
//flag声明
uint8 protect_flg = 0;
uint8 thresold = 55;
/****************************************/
//
//			//-----硬件初始化-----//
//
/****************************************/
uint8 double_car_flg = 1;
void hardware_init()
{
    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置LPTMR的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(PORTE_VECTORn , PORTE_IRQHandler);
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置LPTMR的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(UART0_RX_TX_VECTORn ,UART0_IRQHandler);
    set_vector_handler(UART3_RX_TX_VECTORn ,UART3_IRQHandler);
    enable_irq(PORTA_IRQn);//允许PTA的中断
    enable_irq(PORTE_IRQn);//
    //电机初始化
    ftm_pwm_init(FTM3,FTM_CH1,10000,0);
    ftm_pwm_init(FTM3,FTM_CH3,10000,0);//左正转
    ftm_pwm_init(FTM3,FTM_CH5,10000,0);
    ftm_pwm_init(FTM3,FTM_CH7,10000,0);//右正转
    //舵机初始化
    ftm_pwm_init(FTM0,FTM_CH4,110,DJ_MID);
    gpio_init(PTA5,GPO,0);
    gpio_init(PTA6,GPO,1);
    //按键初始化
    gpio_init(PTC17,GPI,0);
    gpio_init(PTC15,GPI,0);
    gpio_init(PTD4,GPI,0);
//	gpio_init(PTD9,GPI,0);
    gpio_init(PTD2,GPO,1);
    gpio_init(PTD0,GPO,1);
//	gpio_init(PTD8,GPO,1);
    //拨码开关初始化
    gpio_init(PTC4,GPI,0);
    gpio_init(PTC5,GPI,0);
    gpio_init(PTC6,GPI,0);
    gpio_init(PTC7,GPI,0);
 //
    gpio_init(PTC16,GPI,0);
    //gpio_init(PTC17,GPI,0);
    gpio_init(PTC18,GPI,0);
    gpio_init(PTC19,GPI,0);
    
//双车鉴别 PTE25
    gpio_init(PTE25,GPI,0);    
    if(gpio_get(PTE25) == 0)
    {
        double_car_flg =  2;
        if(erwa_go)	Car_State = HOU;
        else	Car_State = QIAN  ;
        thresold = 55;
        gpio_init(PTA6,GPO,0);
        
    }
    else
    {
        double_car_flg = 1;
        Car_State = QIAN;
        thresold = 60;
        gpio_init(PTA6,GPO,1);
    }

    //核心板LED初始化
    gpio_init(PTC0,GPO,1);//灭
    gpio_init(PTA17,GPO,1);
    gpio_init(PTE26,GPO,1);
    gpio_init(PTD15,GPO,1);
    //OLED初始化
    OLED_Init();
    //开启FPU
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));
    //  gpio_init(PTC1,GPO,0);
    //超声波初始化
    gpio_init(PTE11,GPI,0);
    port_init(PTE11,IRQ_EITHER|PULLDOWN|ALT1);
    pit_init_ms(PIT1,25);
    set_vector_handler(PIT1_VECTORn,pit1_hander);   
    enable_irq(PIT1_IRQn);  
    
   //编码器初始化
    ftm_quad_init(FTM1);
    ftm_quad_init(FTM2);
    //UART初始化
    uart_init(UART4,115200);
    uart_init(UART3,9600);
    uart_init(UART0,9600);
    uart_rx_irq_en (UART0);//开接收中断
    uart_rx_irq_en (UART3);//开接收中断
    DELAY_MS(600);
    //摄像头初始化
    ov7725_eagle_init(imgbuff);
    NVIC_SetPriorityGrouping(4);
    NVIC_SetPriority(PORTA_IRQn,4);
    NVIC_SetPriority(DMA0_IRQn,3);
    NVIC_SetPriority(PORTE_IRQn,2);
    NVIC_SetPriority(UART0_RX_TX_IRQn,5);
    NVIC_SetPriority(UART3_RX_TX_IRQn,5);
    NVIC_SetPriority(PIT1_IRQn,1);
    boma();
    turn_flg = overtakedir[0];
}

/****************************************/
//
//			//-----核心板上四个LED-----//
//
/****************************************/
void LED1(uint8 i)
{
    if(i == 1) gpio_set(PTC0,0);//亮
    if(i == 0) gpio_set(PTC0,1);//灭
}

void LED2(uint8 i)
{
    if(i == 1) gpio_set(PTA17,0);//亮
    if(i == 0) gpio_set(PTA17,1);//灭
}
void LED3(uint8 i)
{
    if(i == 1) gpio_set(PTE26,0);//亮
    if(i == 0) gpio_set(PTE26,1);//灭
}
void LED4(uint8 i)
{
    if(i == 1) gpio_set(PTD15,0);//亮
    if(i == 0) gpio_set(PTD15,1);//灭
}
/****************************************/
//
//			//-----拨码开关-----//
//
/****************************************/
int8 speed_mode;
int16 speedhh1[6]={1100,1050,1000,900,850,800};
int16 speedhh2[6]={1100,1050,1000,925,875,825};

int16 speedh1[6] ={1050,1000,950,850,800,750};
int16 speedh2[6] ={1050,1000,950,875,825,775};

int16 speedl1[6] ={1000,950,900,800,750,700};
int16 speed12[6] ={1025,975,925,825,775,725};

int16 speedll1[6] = {950,900,850,750,700,650};
int16 speedll2[6] = {950,900,850,775,725,675};
uint8 round_overtake_enable;
uint8 start_line_overtake_enable;
uint8 get_start_line;
void boma()
{
    uint8 boma_value=0;
    if(gpio_get(PTC7) == 0) boma_value |= 0x02;
    if(gpio_get(PTC6) == 0) boma_value |= 0x01;
      if(gpio_get(PTC4) == 0) 
      {
        round_overtake_enable = 1;
      }
      else round_overtake_enable = 0;
      if(gpio_get(PTC5) == 0) 
      {
       get_start_line = 1;
      }
      else get_start_line = 0;
      if(gpio_get(PTC19) == 0) 
       {
         start_line_overtake_enable = 1;
        }
      else start_line_overtake_enable = 0;
      if(gpio_get(PTC18) == 0) 
       {
         chao_chedir = 0;
        }
      else  chao_chedir = 1;
 
    switch (boma_value)
    {
    case 0x00://0000
      if(Car_State == QIAN)
        for(uint8 i = 0;i<6;i++)
        {
       Hightargetspeed[i] =speedll1[i];
        }
      else      
        for(uint8 i = 0;i<6;i++)
        {
       Hightargetspeed[i] =speedll2[i];
        }
        break;
    case 0x01://0001
            if(Car_State == QIAN)   
              for(uint8 i = 0;i<6;i++)
        {
       Hightargetspeed[i] =speedl1[i];
        }
      else   
        for(uint8 i = 0;i<6;i++)
        {
       Hightargetspeed[i] =speed12[i];
        }
        break;
    case 0x02://0010
        if(Car_State == QIAN) 
             for(uint8 i = 0;i<6;i++)
        {
       Hightargetspeed[i] =speedh1[i];
        }
      else 
              for(uint8 i = 0;i<6;i++)
        {
       Hightargetspeed[i] =speedh2[i];
        }
        break;
    case 0x03://0011
             if(Car_State == QIAN)  
                     for(uint8 i = 0;i<6;i++)
        {
       Hightargetspeed[i] =speedhh1[i];
        }
      else 
                        for(uint8 i = 0;i<6;i++)
        {
       Hightargetspeed[i] =speedhh2[i];
        }
        break;
    }
}
/****************************************/
//
//			//-----按键-----//
//
/****************************************/
uint8 key_value = 10;
PTXn_e Key_Init[3] = {PTC17,PTC15,PTD4};
void key()
{
    uint8 n = 10;
    key_value=10;
    //0 1 1
 	gpio_set(PTD2,0);
	gpio_set(PTD0,1);
//	gpio_set(PTD8,1);

    for(uint8 i = 0; i<3; i++)
    {
        if(gpio_get(Key_Init[i]) == 0)
        {
            DELAY_MS(20);
            while (gpio_get(Key_Init[i]) ==0 )
            {
                n = i + 1;
            }
        }
    }
    //1 0 1
        gpio_set(PTD2,1);
	gpio_set(PTD0,0);
//	gpio_set(PTD8,1);
    for(int8 i = 0; i<3; i++)
    {
        if(gpio_get(Key_Init[i]) == 0)
        {
            DELAY_MS(20);
            while (gpio_get(Key_Init[i]) ==0 )
            {
                n = i + 4;
            }
        }
    }

    key_value = n;
}

/****************************************/
//
//			//-----数码管引脚初始化,共阴极数码管-----//
//
/****************************************/
//PTXn_e num_init[7] = {PTC4,PTC5,PTC6,PTC7,PTC8,PTC9,PTC10};
//uint8 Num_Arr[17][7] =
//{
//	{1,1,1,1,1,1,0},//0
//	{0,1,1,0,0,0,0},//1
//	{1,1,0,1,1,0,1},//2
//	{1,1,1,1,0,0,1},//3
//	{0,1,1,0,0,1,1},//4
//	{1,0,1,1,0,1,1},//5
//	{1,0,1,1,1,1,1},//6
//	{1,1,1,0,0,0,0},//7
//	{1,1,1,1,1,1,1},//8
//	{1,1,1,1,0,1,1},//9
//	{1,1,1,0,1,1,1},//a
//	{0,0,1,1,1,1,1},//b
//	{1,0,0,1,1,1,0},//c
//	{0,1,1,1,1,0,1},//d
//	{1,0,0,1,1,1,1},//e
//	{1,0,0,0,1,1,1},//f
//	{0,0,0,0,0,0,0}//全灭
//};

//数码管显示
//void num(uint8 num)
//{
//	for(uint8 i = 0;i<7;i++)
//		gpio_set(num_init[i],Num_Arr[num][i]);
//}


