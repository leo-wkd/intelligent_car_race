#include "overtake_straight.h"
uint8 straight_flg = 0;
uint8 stragiht_distance = 0;
uint8 straight_getline_end = 0;
uint8 star_flg =0;
uint8 straight_getline_flg = 0;
uint8 straight_speed_flg = 0;
void overatake_straight_speed()
{
    if(erwa_go&&Straight_Overtake_Enable)
    {
        if(straight_flg ==1&&Car_State ==QIAN)
        {
            car.targetspeed = 1000;
            if(ufabs(error)<1.5&&ufabs(error)>1)
                straight_speed_flg = 1;
            if(straight_speed_flg==1)
                car.targetspeed = 0;

        }
    }








}
void overtake_straight_communication()
{










}
void overtake_straight_getline()
{
    if(erwa_go&&Straight_Overtake_Enable)
    {


        if(straight_flg ==1&&Car_State ==QIAN)
        {
            for(uint8 i = 59; i>=l; i--)
            {
                if(double_car_flg ==1)
                {

                    Left[i] = Right[i]-Length1[i]/2;
                }
                else
                {
                    Left[i] =Right[i]-Length2[i]/2;

                }
            }
        }
    }


}

void overtake_straight_jundge()
{
    if(erwa_go&&Straight_Overtake_Enable)
    {
        if(ufabs(error)<5 && l==5&&r==5&&straight_flg!=1&&star_flg==1)
        {
            stragiht_distance+=1;
        }
        if(ufabs(error)<5 && l==5&&r==5&&stragiht_distance>40)
        {

            straight_flg = 1;


        }
        if(straight_flg ==1)
        {
            stragiht_distance = 0;
        }






    }








}