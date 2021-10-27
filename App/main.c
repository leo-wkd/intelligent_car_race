#include "include.h"
void prepare();  //函数声明
uint8 run_flg;


 void main()
{
    DisableInterrupts; //禁止总中断
    printf("\n//-----西北工业大学 双车队-----//\n");


    hardware_init();  //硬件初始化
    parameter_init();  //参数初始化
    EnableInterrupts;

    prepare();
    run_flg = 1;
    DELAY_MS(2000);
#if Double_Car_Mode
    if(Car_State==HOU&&!Start_Line_Overtake)
    {
        Distance = 0;


        while(1)
   

        {
             OLED();
            if(Distance>=35)
                break;
        }

      OLED_Fill(0);	//OLED清屏
   	//后车距离前车15cm以外之后，后车采取跟随模式
    }
    else if(Car_State==HOU)
    {
    Distance = 0;
    while(1)
    {
     if(flag==4)
      break;
    }
    
    
    }
#endif

    //*********************死循环***********************************************//
    while(1)
    {
        
        img_extract(&img[0][0],imgbuff,CAMERA_SIZE);
        protect_detect();  //检测是否出赛道
        if(protect_flg == 1)
            protect();
         GetLine();
       if(Get_Start_Line)
       {
         qipao_stop();
        }
        else stop();
        Cacl_Error();
        Speed_Set();
        Rudder_ctrl();
        Diff_Speed();
        Speed_Get();
        Speed_Ctrl();
        Fm();
        if(flag==77)
        {
           Car_State= HOU;
           Distance_Still_flg = 1;
        }
         OLED();
        while(Pic_complete == 1);
        while(Pic_complete == 0);
    }
}
int32 ti = 0;
void prepare()
{

// OLED_Print(0,0,"比我跑的快");
// OLED_Print(0,3,"都出跑道队");
    DELAY_MS(1000);
//  Draw_BMP(my_PIG);//OLED显示图片

    OLED_Fill(0);

    while(key_value!=5)
    {

        
        img_extract(&img[0][0],imgbuff,CAMERA_SIZE);//解压到二维数组
        GetLine();
        Cacl_Error();
        Speed_Get();	//读取脉冲值
        Speed_Set(); 
        Rudder_ctrl();
        OLED_ctrl();
//         ftm_pwm_duty(FTM3,FTM_CH5,3000);
//          ftm_pwm_duty(FTM3,FTM_CH3,3000);
//      uart_ctrl();

        key_ctrl();
        Fm();
 
        while(Pic_complete == 1);
        while(Pic_complete == 0);
    }
    OLED_Fill(0);	//OLED清屏
}

