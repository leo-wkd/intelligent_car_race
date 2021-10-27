#include "hardware.h"

//函数声明
void CoChange_ctrl();//OLED微调变量
void uart_wave();
void parameter_init();//参数初始化
void adc();

//变量声明
uint16 DJ_MAX = 0;
uint16 DJ_MID = 0;
uint16 DJ_MIN = 0;


//结构体变量定义
Rudder rudder = {0};
Motor motorL = {0};
Motor motorR = {0};
Car car = {0};


/*******************************************************************************参数初始化*/
char Car_State;

uint8 *Length;
uint8 Slope_Threshold;

void parameter_init()
{
    if(double_car_flg == 1)//风驰
    {
        Car_State = QIAN;
        uint8 Err =  183;  //200
        DJ_MID = 1620;
        DJ_MAX = DJ_MID+Err;	//左
        DJ_MIN = DJ_MID-Err;
        rudder.P = 0.15;
        rudder.D = 15;
        rudder.Angle = 1600;
        rudder.Angle_last = 1600;
        Slope_Threshold = 120;

    }

    if(double_car_flg == 2) //电掣
    {
        if(erwa_go)	Car_State = HOU;
        else	Car_State = QIAN  ;
        uint8 Err = 178;
        DJ_MID = 1593;
        DJ_MAX = DJ_MID+Err;	//左
        DJ_MIN = DJ_MID-Err;
        rudder.P = 0.25;
        rudder.D = 15;
        rudder.Angle = 1570;
        rudder.Angle_last = 1570;
        Slope_Threshold = 120;
    }
}
//用于主循环中






void OLED()
{
    static uint16 num_count = 0;
    if(num_count++ == 50)
    {
        num_count = 0;
        OLED_P6x8Str(0,0,"Car");
        OLED_PrintValueI(30,0,double_car_flg);
        OLED_6x8Char(48,0,Car_State);
//		OLED_P6x8Str(0,1,"Wait");	OLED_PrintValueI(30,1,Wait_flg);
        //OLED_P6x8Str(0,2,"X");		OLED_PrintValueI(30,2,(int16)Xielv);
        OLED_P6x8Str(0,3,"A");
        OLED_PrintValueF(30,3,rudder.Angle,0);
        OLED_P6x8Str(0,4,"l");
        OLED_PrintValueI(30,4,l);
        OLED_P6x8Str(0,5,"m");
        OLED_PrintValueI(30,5,m);
        OLED_P6x8Str(0,6,"r");
        OLED_PrintValueI(30,6,r);
        OLED_P6x8Str(0,7,"flag");
        OLED_PrintValueI(30,7,flag);
        OLED_P6x8Str(75,1,"T");
        OLED_PrintValueI(93,1,(uint16)car.targetspeed);
        OLED_P6x8Str(75,2,"Rt");
        OLED_PrintValueI(93,2,(uint16)motorR.targetspeed);
        OLED_P6x8Str(75,3,"Lt");
        OLED_PrintValueI(93,3,(uint16)motorL.targetspeed);
        OLED_P6x8Str(75,4,"Pr");
        OLED_PrintValueI(93,4,pulse_R);
        OLED_P6x8Str(75,5,"Pl");
        OLED_PrintValueI(93,5,pulse_L);
        OLED_P6x8Str(75,6,"Dis");
        OLED_PrintValueI(93,6,Distance);
        OLED_P6x8Str(75,7,"f");
        OLED_PrintValueI(93,7,(int16)turn_flg);
    }
}
///********************************************OLED显示函数*/
void OLED_ctrl()
{
    static uint16 OLED_i = 0;
    OLED_i++;//控制OLED刷新频率，防止OLED显示频率过快
    if(OLED_i == 500)//防止OLED花屏，隔几秒重新初始化OLED
    {
        OLED_i = 0;
        OLED_Init();
    }


    static uint8 OLED_flg = 0;
    if(key_value == 3) //key3翻页

    {

        OLED_flg++;

        OLED_Fill(0);
    }

    switch(OLED_flg%3)
    {
    case 0:
        //--------显示图像
        Oled_Img(&img[0][0]);
        //------显示变量
        if(OLED_i%50 == 0) //reason：OLED显示频率过快
        {
            OLED_P6x8Str(80,0,"Car");
            OLED_PrintValueI(98,0,double_car_flg);
            OLED_6x8Char(114,0,Car_State);
            OLED_P6x8Str(80,1,"s");
            OLED_PrintValueI(98,1,Slope_flg);
            OLED_P6x8Str(80,2,"E");
            OLED_PrintValueI(86,2,(uint16)error);
            OLED_P6x8Str(80,3,"A");
            OLED_PrintValueF(86,3,rudder.Angle,0);
            OLED_P6x8Str(80,4,"l");
            OLED_PrintValueI(98,4,l);
            OLED_P6x8Str(80,5,"m");
            OLED_PrintValueI(98,5,m);
            OLED_P6x8Str(80,6,"r");
            OLED_PrintValueI(98,6,r);
            //OLED_PrintValueF(0,7,Xielv,3); OLED_PrintValueF(60,7,Xielv,3);
            //OLED_P6x8Str(80,7,"f");		OLED_PrintValueI(98,7,stop_flg);
        }
        break;
    case 1:
        //------显示变量
        if(OLED_i%50 == 0) //reason：OLED显示频率过快
        {
            OLED_P6x8Str(10,0,"L_target");
            OLED_PrintValueI(58,0,(uint16)motorL.targetspeed);
            OLED_P6x8Str(10,1,"R_target");
            OLED_PrintValueI(58,1,(uint16)motorR.targetspeed);
            OLED_P6x8Str(10,2,"servo.Angle");
            OLED_PrintValueI(58,2,(uint32)rudder.Angle);
            OLED_P6x8Str(10,3,"Distance");
            OLED_PrintValueI(58,3,Distance);
            OLED_P6x8Str(10,4,"pulse_L");
            OLED_PrintValueI(58,4,pulse_L);
            OLED_P6x8Str(10,5,"pulse_R");
            OLED_PrintValueI(58,5,pulse_R);
            OLED_P6x8Str(10,6,"DJ_MID");
            OLED_PrintValueI(58,6,DJ_MID);
            OLED_P6x8Str(10,7,"target");
            OLED_PrintValueI(58,7,(uint16)car.targetspeed);
        }
        break;
    case 2:
        CoChange_ctrl();

        if(OLED_i%50 == 0)
        {
            OLED_P6x8Str(10,5,"curv");
            OLED_PrintValueF(58,5,curv,5);
            OLED_P6x8Str(10,3,"rudder.P");
            OLED_PrintValueF(58,3,rudder.P,2);
            OLED_P6x8Str(10,4,"rudder.D");
            OLED_PrintValueF(58,4,rudder.D,2);
//		  OLED_P6x8Str(10,5,"Slope");		OLED_PrintValueI(58,5,Slope_Distance);
            OLED_P6x8Str(10,6,"Xielv");
            OLED_PrintValueF(58,6,Xielv,3);

            OLED_P6x8Str(10,7,"car.error");
            OLED_PrintValueI(58,7,(uint16)(car.error));
//		  OLED_P6x8Str(10,6,"kkd");			OLED_PrintValueF(58,6,kkd,2);
//		  OLED_P6x8Str(10,7,"kkd");			OLED_PrintValueF(58,7,kkd,2);
        }
        break;

    default:
        break;
    }
}

///*******************************************************************************CAR TO COMPUTER*/
void uart_CTP(uint8 line)
{
    produceCamRoadData(line);
    sendRoadDataToCamViewer(camLineData);  //发送赛道数据到上位机
}

void uart_ctrl()
{
    static uint8 uart_flg = 0;
    if(key_value == 2) uart_flg++;

    switch (uart_flg%3+1)
    {
    case 2:
        uart_CTP(1);
        break;//发送中线
    case 1:
        uart_CTP(2);
        break;//发送双线
    case 3:
        uart_wave();
        break;//发送变量
    default:
        break;
    }
}
/***************************************************换行函数*/
void CoChange_ctrl()
{
    static uint8 CoChange_flg = 0;
    if(key_value == 1) CoChange_flg++;
    uint8 co = CoChange_flg % 8;

    OLED_P6x8Str(0,co==0?7:co-1," ");
    OLED_P6x8Str(0,co,"#");

    switch(co)
    {
    case 0:
        break;

    case 1:
        break;

    case 2:
        //  if(key_value == 5) car.D += 1;
        //  if(key_value == 6) car.D -= 1;
        break;

    case 3:
        if(key_value == 5) rudder.P += 0.1;
        if(key_value == 6) rudder.P -= 0.1;
        break;

    case 4:
        if(key_value == 5) rudder.D += 0.5;
        if(key_value == 6) rudder.D -= 0.5;
        break;

    case 5:
        if(key_value == 5)
        {
        }
        if(key_value == 6)
        {
        }
        break;

    case 6:
        if(key_value == 5)
        {
        }
        if(key_value == 6)
        {
        }
        break;

    case 7:
        break;

    default:
        break;
    }
}


uint8 cross_ctrl = 0;
void key_ctrl()
{
    key();
    switch(key_value)
    {
    case 1:
        //car.targetspeed += 50;
        break;
    case 2:
        //  DJ_MID += 1;
    case 3:
        //  DJ_MID -= 5;
        break;
    }
}


void uart_wave()
{
   
    
    //左轮
    push(0,(uint16)motorL.targetspeed);
    push(1,motorL.pulse);
    push(2,(int32)motorL.PWM_out/10);
    //右轮
    push(3,(uint16)motorR.targetspeed);
    push(4,motorR.pulse);
    push(5,(int32)motorR.PWM_out/10);
    //舵机
    push(6,(int16)error);
    push(7,(uint32)rudder.Angle);
    push(8,(int16)qian_speed);
    //others
    push(9,(uint16)Distance);
    push(10,(int16)car.error);//发送car state
    push(11,car.trend);
    //11 用于直道超车

    sendDataToScope();
}


/********************************************检测是否出赛道*/
void protect_detect()
{
    uint8 white_num = 0;
    for(uint8 i=0; i<=LINE; i++)
    {
        if(img[ROW][i]>=100)
            white_num++;
    }
    if(white_num<=5)
        protect_flg = 1;
}

//******保护程序*/
void protect()
{
    uint8 put_num;
    while(1)
    {
        ftm_pwm_duty(FTM0,FTM_CH3,(uint32)rudder.Angle_last);
        //num(A_);
        uint8 test_flg = 77;
        if(put_num<=5)
       {
        car_send(TYPE_FLAG,&test_flg);
        put_num++;
       }
        car.targetspeed = 0;
        Diff_Speed();
        Speed_Get();
        Speed_Ctrl();
    }
}
void Fm()
{
    if(round_flg== 1)
        gpio_set(PTA5,1);
    else gpio_set(PTA5,0);
}
