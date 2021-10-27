#include "Control.h"
/****************************************************************************
 舵机控制函数（pd控制） 2016.11.18 罗鹏涛
*****************************************************************************/

//************************代码部分*******************************************//
void Rudder_ctrl()
{
    if(m<55)
    {

        if(double_car_flg==1)  //1che
        {

            /*if(ufabs(Xielv)<0.3 ) { rudder.Kp = 2.5;rudder.Kd = 15;}

                       else*/
            if(ufabs(Xielv)<0.5 )
            {
                rudder.Kp = 3.5;
                rudder.Kd = 15;
            }


            else if(ufabs(Xielv)<0.8)
            {
                rudder.Kp = 4 ;
                rudder.Kd = 15;
            }

            else
            {
                rudder.Kp =  ufabs(Xielv)*5;
                rudder.Kd = 15;
            }
            //  rudder.Kp = rudder.P * ufabs(error);

            if(rudder.Kp>6.5)        rudder.Kp = 6.5;
            if(round_rudder_flg == 1||out_flg==1) rudder.Kp = 7;
            if(shizi_flg)  rudder.Kp = 8;
          
        }
        else   //2che
        {

            /* if(ufabs(Xielv)<0.3 ) { rudder.Kp = 3;rudder.Kd = 15;}

                      else */
          if(ufabs(Xielv)<0.5)
            {
                rudder.Kp = 4;
                rudder.Kd = 15;
            }

            else if(ufabs(Xielv)<0.8)
            {
                rudder.Kp = 4.5;
                rudder.Kd = 15;
            }

            else
            {
                rudder.Kp =  ufabs(Xielv)*5.5;
                rudder.Kd= 15 ;
            }
            //  rudder.Kp = rudder.P * ufabs(error);

            if(rudder.Kp>6.6)        rudder.Kp = 6.6;
          //  if(shizi_flg)  rudder.Kp =6.6;
          if(round_rudder_flg == 1||out_flg==1) rudder.Kp = 7;
           
        }

        rudder.Angle = DJ_MID -rudder.Kp*error - rudder.Kd*derror;

    }
    else
    {
        rudder.Angle = rudder.Angle_last;
    }

    if(GetLine_Error_flg == 1)    rudder.Angle = rudder.Angle_last;
    if(rudder.Angle>DJ_MAX) rudder.Angle = DJ_MAX;
    if(rudder.Angle<DJ_MIN) rudder.Angle = DJ_MIN;

    ftm_pwm_duty(FTM0,FTM_CH4,(uint32)rudder.Angle);

    rudder.Angle_last = rudder.Angle;
}
