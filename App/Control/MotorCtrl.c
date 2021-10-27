

#include "Control.h"
/******************************************************************************
电机控制函数（设置速度  差速  pid ） 2016.12 .01 罗鹏涛
*******************************************************************************/

//****************************代码部分****************************************//
int16 pulse_L = 0,pulse_R = 0;
int16 speed_ave = 0;
void Slope_Speed();
void round_speed();
void qian_speed_ctrl();
void hou_speed_ctrl();
void round_overtake_speedqian();
void  round_overtake_speedhou();
void Speed_Get()
{

    pulse_R = 4*ftm_quad_get(FTM1);
    pulse_R = -pulse_R;
    ftm_quad_clean(FTM1);
    pulse_L = 4*ftm_quad_get(FTM2);
    ftm_quad_clean(FTM2);
    speed_ave=(pulse_L+pulse_R)/2;

}

//uint16 Hightargetspeed[6] = {1250,1200,1150,850,800,750};//2车
void Distance_Ctrl()
{
    float Fe = 0;
    int16 add = 0;
    //减速控制
    if(Distance<=130 &&Distance_Still_flg!=1)
    {
        Fe = 8;
    }
    else if(Distance>130)
    {
        Fe = 3;
    }
    add = (int16)(Fe*((uint16)Distance - 130));
    if(add > 100) add = 100;
    if(add < -150) add = -150;
    if(!Distance_Still_flg)
    car.targetspeed =(qian_speed*2/10+car.targetspeed*8/10)+add;
    if(Distance_Still_flg)
    {

        car.targetspeed =car.targetspeed;
    }
}
uint16 speed_point = 0;
uint16 speed_long = 0;
uint8 jiasu_e = 0;
uint8 jiansu_e = 0;
uint8 roundspeed_flg;
uint8 big_continue;
int32 big_rounddis = 0;
int32 small_rounddis = 0;
uint8 round_continue =0;
int32 round_end_flg = 0;
int64 round_distance = 0;
int16 Hightargetspeed[6];
//int8  overtakedir[10] = {0,1,0,0,0,0,0,0,0,0}; //1  L  
int8  overtakedir[10] = {1,0,1,0,0,0,0,0,0,0};
uint8 chao_checishu = 0;
uint8 moren_turn = 0;
int32 put_num;
int32 sdis = 0;
int32 bdis = 0;
int32 start_dis = 0;
int32 ssdis = 0;
int32 bbdis = 0;
void Speed_Set()
{
   if(double_car_flg == 1)
    {
        speed_long = 7;
        jiasu_e = 12;
        jiansu_e = 13;

    }
    else  
    {
        speed_long = 7;
        jiasu_e = 12;
        jiansu_e = 13;
    }
    speed_point = m+1>speed_long?m+1:speed_long;
    car.error=0;
    uint8 i=speed_point;
    for(; i<=(speed_point+2<=ROW?speed_point+2:ROW); i++)
    {
        car.error += Mid[i]-40;

    }
    car.error/=3;
    car.error =(int16)(0.5*car.error+0.5*car.error_last);
    if(car.error>30) car.error = 30;
    if(car.error<-30) car.error = -30;


    Uderror = uabs16(car.error)-uabs16(car.error_last);
    car.error_last=car.error;

//
    if(Uderror<2&&car.trend<31&& ufabs(car.error)<=jiasu_e)
    {
        car.trend += 2;
    }
    else if(Uderror>=2 && ufabs(car.error)>=jiansu_e)
    {
        car.trend /= 2;

    }


    if(double_car_flg == 1)

    {
        if(car.trend>=30)       car.targetspeed  = (int16)(Hightargetspeed[0]-ufabs(((uint16)rudder.Angle-DJ_MID)*1.0/(DJ_MAX-DJ_MID)*40));
        else if(car.trend>=25)  car.targetspeed  = (int16)(Hightargetspeed[1]-ufabs(((uint16)rudder.Angle-DJ_MID)*1.0/(DJ_MAX-DJ_MID)*40));//60
        else if(car.trend>=20)  car.targetspeed  = (int16)(Hightargetspeed[2]-ufabs(((uint16)rudder.Angle-DJ_MID)*1.0/(DJ_MAX-DJ_MID)*40));//40
        else if(car.trend>=15)  car.targetspeed  = (int16)(Hightargetspeed[3]-uabs16((uint16)rudder.Angle-DJ_MID)/2);//2
        else if(car.trend>=11)  car.targetspeed  = (int16)(Hightargetspeed[4]-uabs16((uint16)rudder.Angle-DJ_MID)/3);//3  5
        else                    car.targetspeed  = (int16)(Hightargetspeed[5]-uabs16((uint16)rudder.Angle-DJ_MID)/4);//4  5


    }

    else

    {
        if(car.trend>=30)       car.targetspeed  = (int16)(Hightargetspeed[0]-ufabs(((uint16)rudder.Angle-DJ_MID)*1.0/(DJ_MAX-DJ_MID)*40));
        else if(car.trend>=25)  car.targetspeed  = (int16)(Hightargetspeed[1]-ufabs(((uint16)rudder.Angle-DJ_MID)*1.0/(DJ_MAX-DJ_MID)*40));//60
        else if(car.trend>=20)  car.targetspeed  = (int16)(Hightargetspeed[2]-ufabs(((uint16)rudder.Angle-DJ_MID)*1.0/(DJ_MAX-DJ_MID)*40));//40
        else if(car.trend>=15)  car.targetspeed  = (int16)(Hightargetspeed[3]-uabs16((uint16)rudder.Angle-DJ_MID)/2);//2
        else if(car.trend>=11)  car.targetspeed  = (int16)(Hightargetspeed[4]-uabs16((uint16)rudder.Angle-DJ_MID)/3);//3  5
        else                    car.targetspeed  = (int16)(Hightargetspeed[5]-uabs16((uint16)rudder.Angle-DJ_MID)/4);//4  5

    }
    if(!Double_Car_Mode)
    {
        round_speed(); //环岛速度控制
        Slope_Speed();
    }
   
    if(sstop_flg ==1) car.targetspeed = (int16)(Hightargetspeed[0]);
   
    if(sround_start==1) 
   {
       sdis+=speed_ave;
   }
   if(sdis>=15000&&!Round_Overtake_Enable&&Car_State==HOU)
   {
    flag = 0;
   }
   
   if(sdis>=80000) 
   {
    sdis = 0;
    sround_start = 0;
    
   }
     if(bround_start==1) 
   {
     bdis+=speed_ave;
   }
     if(bdis>=15000&&!Round_Overtake_Enable&&Car_State==HOU)
   {
    flag = 0;
   }
   if(bdis>=100000)
   {
       bdis = 0;
       bround_start = 0;
   }
   
#if Double_Car_Mode
    uint8 value = 0;
    if(Round_Overtake_Enable) value|=0x01;
    if(Start_Line_Overtake)   value|=0x02;
    switch(value)
    {
    case 0x00:     //两个超车都没有 
          if(Car_State==QIAN)
        {
            qian_speed_ctrl();
       

        }
        if(Car_State ==HOU&&flag!=8)
        {
            hou_speed_ctrl();
            if(flag==99)  car.targetspeed = 600;
            if(flag==100) car.targetspeed = 600;
        }
        break;
    case 0x01: //环岛超车打开 直道超车没有
         if(Car_State==QIAN)
        {
          round_overtake_speedqian();
        }
        else if(Car_State==HOU)
        {
          round_overtake_speedhou();
        }
        break;
    case 0x02:   //只有直道超车
       if(!start_finish_flg)
       {
       if(Car_State==QIAN)
      {  
        uint8 put_flg = 0;  
        start_dis+=speed_ave;
      if(start_dis>=14000)
      {
       car.targetspeed = 0;
       if(put_flg<=2)
       {  
       uint8 test_flg = 4;
       car_send(TYPE_FLAG,&test_flg);
       car_send(TYPE_FLAG,&test_flg);
       put_flg++;
       }
       }
      if(flag==3)
       {
       start_finish_flg = 1;
       start_dis = 0;
       Car_State=HOU;
       flag =0;
       }
      }
      else if(Car_State==HOU)
      {
          start_dis+=speed_ave;
           if(start_dis>=30000&&flag==4)
          {
           uint8 test_flg = 3;
           car_send(TYPE_FLAG,&test_flg);
           car_send(TYPE_FLAG,&test_flg);
           start_dis = 0;
           Car_State=QIAN; 
           flag = 0;
           start_finish_flg = 1;
           }
       }
     }
     else if(start_finish_flg)
     {
        if(Car_State==QIAN)
        {
          qian_speed_ctrl();

        }
        if(Car_State ==HOU&&flag!=8)
        {
            hou_speed_ctrl();    
            if(flag==99)  car.targetspeed = 600;
            if(flag==100) car.targetspeed = 600;   
        }
      }
      break;
    case 0x03:
          if(!start_finish_flg)
       {
               if(Car_State==QIAN)
              {  
                uint8 put_flg = 0;  
                start_dis+=speed_ave;    
                if(flag==3)
              {
                start_finish_flg = 1;
                start_dis = 0;
                Car_State=HOU;
                flag =0;
               }
              if(start_dis>=14000)
              {
                   car.targetspeed = 0;
                   if(put_flg<=2)
                   {  
                   uint8 test_flg = 4;
                   car_send(TYPE_FLAG,&test_flg);
                   car_send(TYPE_FLAG,&test_flg);
                   put_flg++;
                   }
               }
         
      }
      else if(Car_State==HOU)
              {
                 start_dis+=speed_ave;
                 if(start_dis>=30000&&flag==4)
                {
                     uint8 test_flg = 3;
                     car_send(TYPE_FLAG,&test_flg);
                     car_send(TYPE_FLAG,&test_flg);
                     start_dis = 0;
                     Car_State=QIAN; 
                     flag = 0;
                     start_finish_flg = 1;
                 }
           }
      }
     else if(start_finish_flg)
        {
          if(Car_State==QIAN)
            {
                round_overtake_speedqian();
            }
           if(Car_State==HOU)
           {
                round_overtake_speedhou();
           }
       }
       break;
     }
      
#endif

}
void round_speed()
{
    if(roundspeed_flg == 1)

    {
        round_continue = 1;
        car.targetspeed = 600;
    }

    if(round_continue ==1 && roundspeed_flg == 0)
    {
        car.targetspeed = 600;
        car.trend = 0;
        round_distance+=speed_ave;

    }
    if(round_distance>20000)
    {
        round_end_flg = 1;
    }
    if(round_end_flg == 1 && round_continue ==1)
    {
        round_continue = 0;
        round_end_flg  = 0;
        round_distance = 0;
    }
}
int8 Slope = 1;
uint8 Slope_continue=0;
int32 Slope_distance = 0;
int32 Meaure_distance = 0;

void Slope_Speed()
{
    if(Slope_flg == 1&&Slope == 1)
    {
        car.targetspeed = 850;
        Slope = 0 ;
        Slope_distance+= speed_ave;
        Meaure_distance+= speed_ave;
    }
    if(Slope_distance>= 400)
    {
        car.targetspeed = 850;
        Slope_distance+= speed_ave;
        Meaure_distance+= speed_ave;
    }

    if(Slope_distance>30000)
    {
        Slope_distance = 0;

    }
    if(Slope == 0 )
    {
        Meaure_distance+= speed_ave;
    }

    if(Meaure_distance>100000)
    {

        Slope = 1;
        Meaure_distance = 0;
    }

}
void qian_speed_ctrl()
{
      round_speed(); //环岛速度控制
      Slope_Speed();
      uint16 test_speed;
      test_speed =speed_ave;
      if(speed_ave<0) test_speed = 0;
      car_send(TYPE_SPEED,&test_speed);
}
void round_overtake_speedqian()
{
          if(roundspeed_flg)
            {
                car.targetspeed = 500;
            }

            if(round_flg)
            {
                round_continue = 1;
            }
            if(round_flg&&big_flg)
            {
                big_continue = 1;
            }
            else if(!round_continue)
            {
                Slope_Speed();
                uint16 test_speed;
                test_speed =speed_ave;
               
                if(speed_ave<0) test_speed = 0;
                car_send(TYPE_SPEED,&test_speed);
           }
            if(round_continue&&!big_continue)
            {

                car.targetspeed = 600;
                small_rounddis+=speed_ave; //距离积分
            }
            if(round_continue&&big_continue)
            {
                car.targetspeed = 700;
                big_rounddis+=speed_ave; //距离积分
            }
            if(big_rounddis>=32000)
            {
                car.targetspeed = 0;
            }
            if(small_rounddis>=27000)
            {
                car.targetspeed = 0;
            }

            if(flag==11)
            {
                big_rounddis = 0;
                turn_flg = 1;
                big_continue = 0;
                round_continue = 0;
                small_rounddis  = 0;
                Car_State = HOU;
                flag = 0;
                chao_checishu++;
                Distance_Still_flg = 1;
            }
            else if(flag==12)
            {
                big_rounddis = 0;
                turn_flg = 0;
                big_continue = 0;
                round_continue = 0;
                small_rounddis  = 0;
                Car_State = HOU;
                flag = 0;
                chao_checishu++;
                Distance_Still_flg = 1; 
            }


}
void hou_speed_ctrl()
{
      Slope_Speed();    
      Distance_Ctrl();
      round_speed(); //环岛速度控制 
}
void round_overtake_speedhou()
{
           if(flag==8)
            {

            }
            else  if(flag!=10&&flag!=9&&flag!=13&&flag!=14)
            {
                Slope_Speed();
                Distance_Ctrl();
            }
            else  if(flag==10||flag==9)
            {
                if(roundspeed_flg)
                {
                    car.targetspeed = 600;
                }
                else
                {
                    car.targetspeed = 800;
                }
                if(round_flg)
                {
                    round_continue = 1;
                }
                if(round_continue)
                {
                    car.targetspeed = 600;
                    small_rounddis+=speed_ave; //距离积分
                }
                if(small_rounddis>36000||(small_rounddis>10000&&out_flg))
                {

                    small_rounddis = 0;
                    round_continue = 0;
                    big_rounddis = 0;
                    if(turn_flg==0)
                    {
                        uint8 testflag = 11;
                        car_send(TYPE_FLAG,&testflag);
                        car_send(TYPE_FLAG,&testflag);
                    }
                    else
                    {
                        uint8 testflag = 12;
                        car_send(TYPE_FLAG,&testflag);
                        car_send(TYPE_FLAG,&testflag);
                    }
                    Car_State = QIAN;
                    flag = 0;
                    chao_checishu++;
                }
            }
             else if(flag==14||flag==13)
            {
                      if(round_flg)
                      {
                          round_continue = 1;
                      }
                      if(round_continue)
                      {
                          car.targetspeed = 800;
                          big_rounddis+=speed_ave; //距离积分
                      }
                      if(big_rounddis>=60000)
                      {
                          big_rounddis = 0;
                          small_rounddis = 0;
                          round_continue = 0;
                          big_continue = 0;
                          if(turn_flg==0)
                          {
                              uint8 testflag = 11;
                              car_send(TYPE_FLAG,&testflag);
                              car_send(TYPE_FLAG,&testflag);
                          }
                          else
                          {
                              uint8 testflag = 12;
                              car_send(TYPE_FLAG,&testflag);
                              car_send(TYPE_FLAG,&testflag);
                          }
                          Car_State = QIAN;
                          flag = 0;
                          chao_checishu++;
                     }
              }
}
float k1 = 0;
float k2 = 0;
float k21 = 0;
float k22 = 0;
uint16 angle = 0;
void Diff_Speed()
{
    double tan[81]= {0.0000,
                     0.0175,0.0349,0.0524,0.0699,0.0875,
                     0.1051,0.1228,0.1405,0.1584,0.1763,
                     0.1944,0.2126,0.2309,0.2493,0.2679,
                     0.2867,0.3057,0.3249,0.3443,0.3640,
                     0.3839,0.4040,0.4245,0.4452,0.4663,
                     0.4877,0.5095,0.5317,0.5543,0.5774,
                     0.6009,0.6249,0.6494,0.6745,0.7002,
                     0.7265,0.7536,0.7813,0.8098,0.8391,
                     0.8693,0.9004,0.9325,0.9657,1.0000,
                     1.0355,1.0724,1.1106,1.1504,1.1918,
                     1.2349,1.2799,1.3270,1.3764,1.4281,
                     1.4826,1.5399,1.6003,1.6643,1.7321,
                     1.8040,1.8807,1.9626,2.0503,2.1445,
                     2.2460,2.3559,2.4751,2.6051,2.7475,
                     2.9042,3.0777,3.2709,3.4874,3.7321,
                     4.0108,4.3315,4.7046,5.1446,5.6713
                    };
    if(ufabs(rudder.Angle-DJ_MID)>40)
    {
        if(double_car_flg==1)
        {
            angle=(uint32)((abt((uint32)rudder.Angle,DJ_MID)*4/10)) ;
            k1=0.59;
            k21=1.0+k1*18*tan[angle]/(tan[angle]*18+40);
            k22=1.0-k1*18*tan[angle]/(tan[angle]*18+40);
            if((rudder.Angle-DJ_MID)<0)
            {
                motorL.targetspeed = car.targetspeed*k21;

                motorR.targetspeed = car.targetspeed*k22;
            }
            if((rudder.Angle-DJ_MID)>0)
            {
                motorL.targetspeed = car.targetspeed*k22;

                motorR.targetspeed = car.targetspeed*k21;
            }
        }
//b为待测量，k1，k2为调试量,其中a可以改变差速大小，k可以控制差速的提前与滞后。
        if(double_car_flg==2)
        {
            angle=(uint32)((abt((uint32)rudder.Angle,DJ_MID)*4/10)) ;
            k1=0.53;
            k21=1.0+k1*18*tan[angle]/(tan[angle]*18+40);
            k22=1.0-k1*18*tan[angle]/(tan[angle]*18+40);
            if((rudder.Angle-DJ_MID)<0)
            {
                motorL.targetspeed = car.targetspeed*k21;

                motorR.targetspeed = car.targetspeed*k22;
            }
            if((rudder.Angle-DJ_MID)>0)
            {
                motorL.targetspeed = car.targetspeed*k22;

                motorR.targetspeed = car.targetspeed*k21;
            }
        }
    }
    else
    {

        motorL.targetspeed = car.targetspeed ;

        motorR.targetspeed = car.targetspeed ;

    }

    if(motorL.targetspeed<0)    motorL.targetspeed = 0;

    if(motorL.targetspeed>1700)  motorL.targetspeed = 1700;

    if(motorR.targetspeed<0)    motorR.targetspeed = 0;

    if(motorR.targetspeed>1700)  motorR.targetspeed = 1700;
}
int32 PID_BangBang(Motor *motor)
{
    motor->speed_error = motor->targetspeed-motor->pulse;

    motor->speed_derror = motor->speed_error-motor->speed_error_last;

    motor->speed_error_last = motor->speed_error;

    motor->speed_dderror = motor->pulse - motor->pulse_last;
    if(double_car_flg == 1)
    {
        if(motor->speed_error<400 && motor->speed_error>-300)
        {


            if(car.targetspeed > Hightargetspeed[3])

            {
                motor->Kp = 1.8;
                motor->Kd = 26;
                motor->Kdd = 0;
            }
            else
            {
                motor->Kp = 0.8;
                motor->Kd = 20;
                motor->Kdd =0;
            }

            motor->PWM_out += motor->Kp * motor->speed_error + motor->Kd*motor->speed_derror-motor->Kdd *motor->speed_dderror;

        }
        else if(motor->speed_error>=400)    motor->PWM_out=9000;
        else if(motor->speed_error<=-300 )  motor->PWM_out=-9000;
    }
    if(double_car_flg == 2)
    {
        if(motor->speed_error<400 && motor->speed_error>-300)
        {
            if(car.targetspeed > Hightargetspeed[3])

            {
                motor->Kp = 1.7;
                motor->Kd = 28;
                motor->Kdd = 0;
            }
            else
            {
                motor ->Kp = 0.7;
                motor ->Kd = 24;
                motor->Kdd = 0;
            }

            motor->PWM_out += motor->Kp * motor->speed_error + motor->Kd*motor->speed_derror - motor->Kdd *motor->speed_dderror;
        }
        else if(motor->speed_error>=400)    motor->PWM_out=9000;
        else if(motor->speed_error<=-300)   motor->PWM_out=-9000;
    }
    if(motor->PWM_out>9000)     motor->PWM_out = 9000;
    if(motor->PWM_out<-9000)     motor->PWM_out = -9000;
    return (int32)(motor->PWM_out);
}

void Speed_Ctrl()
{
    int32 Pwm_L,Pwm_R;
    Motor *motor;


    pulse_L = (int16)(motorL.pulse + 0.25 *(pulse_L-motorL.pulse));
    pulse_R = (int16)(motorR.pulse + 0.25 *(pulse_R-motorR.pulse));
    motorL.pulse_last = motorL.pulse;
    motorR.pulse_last = motorR.pulse;
//    if((pulse_L-motorL.pulse)> 150 &&(pulse_R- motorR.pulse )> 150)
//    {
//        pulse_L = motorL.pulse + 60;
//        pulse_R = motorR.pulse + 60;
//    }

    motorL.pulse = pulse_L;
    motorR.pulse = pulse_R;

    motor =&motorL;
    Pwm_L=PID_BangBang(motor);

    if(Pwm_L>=0)
    {
        ftm_pwm_duty(FTM3,FTM_CH3,0);
        ftm_pwm_duty(FTM3,FTM_CH1,(uint32)Pwm_L);
    }
    else
    {
        ftm_pwm_duty(FTM3,FTM_CH3,(uint32)(-Pwm_L));
        ftm_pwm_duty(FTM3,FTM_CH1,0);
    }

    motor = &motorR;
    Pwm_R=PID_BangBang(motor);

    if(Pwm_R>=0)
    {
        ftm_pwm_duty(FTM3,FTM_CH5,0);
        ftm_pwm_duty(FTM3,FTM_CH7,(uint32)Pwm_R);
    }
    else
    {
        ftm_pwm_duty(FTM3,FTM_CH5,(uint32)(-Pwm_R));
        ftm_pwm_duty(FTM3,FTM_CH7,0);

    }

}

