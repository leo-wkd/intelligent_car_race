#include "include.h"
void prepare();  //��������
uint8 run_flg;


 void main()
{
    DisableInterrupts; //��ֹ���ж�
    printf("\n//-----������ҵ��ѧ ˫����-----//\n");


    hardware_init();  //Ӳ����ʼ��
    parameter_init();  //������ʼ��
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

      OLED_Fill(0);	//OLED����
   	//�󳵾���ǰ��15cm����֮�󣬺󳵲�ȡ����ģʽ
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

    //*********************��ѭ��***********************************************//
    while(1)
    {
        
        img_extract(&img[0][0],imgbuff,CAMERA_SIZE);
        protect_detect();  //����Ƿ������
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

// OLED_Print(0,0,"�����ܵĿ�");
// OLED_Print(0,3,"�����ܵ���");
    DELAY_MS(1000);
//  Draw_BMP(my_PIG);//OLED��ʾͼƬ

    OLED_Fill(0);

    while(key_value!=5)
    {

        
        img_extract(&img[0][0],imgbuff,CAMERA_SIZE);//��ѹ����ά����
        GetLine();
        Cacl_Error();
        Speed_Get();	//��ȡ����ֵ
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
    OLED_Fill(0);	//OLED����
}

