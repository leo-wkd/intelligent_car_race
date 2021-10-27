#include "Control.h"
/****************************************************************************
 中线处理函数  2016.11.18 罗鹏涛
*****************************************************************************/

//************************代码部分*******************************************//

/****************************************/
/****************************************/
//
//			//-----最小二乘法计算斜率-----//
//
/****************************************/
float Xielv = 0,Xielv_last = 0;
uint8 Ctrlpoint = 10;
void Least_Square_Method()
{
    int32 xx_sum=0,xy_sum=0,x_sum=0,y_sum=0;
    uint8 count = 0;
    for(uint8 i=ROW; i>Ctrlpoint; i--)
    {
        x_sum += (ROW-i);
        y_sum += Mid[i];
        xx_sum += (ROW-i)*(ROW-i);
        xy_sum += Mid[i]*(ROW-i);
        count++;
    }
    if(count!=0)
        if(xx_sum-x_sum*x_sum*1.0/count != 0)
            Xielv = (float)((xy_sum-x_sum*y_sum*1.0/count)/(xx_sum-x_sum*x_sum*1.0/count));

    Xielv = Xielv>1.5?1.5:Xielv;
    Xielv = Xielv<-1.5?-1.5:Xielv;
    Xielv = 0.7*Xielv+0.3*Xielv_last;//0.4  0.6
    Xielv_last = Xielv;
}
/*******************************************/

float curv = 0;
uint32 AB = 0 ;
uint32 BC = 0 ;
uint32 AC = 0 ;
uint32 S  = 0 ;
void Get_Curv()  //求曲率函数
{
    if(m < 10 )
    {
        AB = Sqrt(625 +uabs32(Mid[55]-Mid[30])*uabs32(Mid[55]-Mid[30]));
        BC = Sqrt((29-m)*(29-m)+uabs32(Mid[30]-Mid[m+1])*uabs32(Mid[30]-Mid[m+1]));
        AC = Sqrt((54-m)*(54-m)+uabs32(Mid[55]-Mid[m+1])*uabs32(Mid[55]-Mid[m+1]));
        S  = uabs32(25*(Mid[m+1]-Mid[55])-((m+1-55)*(Mid[30]-Mid[55])));
        S  = S/2;
        curv = (4*S)/(AB*AC*BC);
    }
    else  if(m  < 30)
    {
        AB = Sqrt(100 +uabs32(Mid[55]-Mid[40])*uabs32(Mid[55]-Mid[40]));

        BC = Sqrt((14-m)*(14-m)+uabs32(Mid[40]-Mid[m+1])*uabs32(Mid[40]-Mid[m+1]));

        AC = Sqrt((54-m)*(54-m)+uabs32(Mid[55]-Mid[m+1])*uabs32(Mid[55]-Mid[m+1]));

        S  = uabs32(15*(Mid[m+1]-Mid[55])-((m+1-55)*(Mid[40]-Mid[55])));

        S  = S/2;

        curv = (4*S)/(AB*AC*BC);
    }
    else
    {

        curv = 0;

    }
}
float error = 0,error_pre[4] = {0},derror = 0;
float error_last = 0;
uint16 Uderror = 0;
uint8 chao_chedir;
void Find_Crtlpoint()
{
    if(double_car_flg == 1)  //一车前瞻有效行数
    {
        if(speed_ave>1100)
            Ctrlpoint = 7;
        else if(speed_ave>850)
            Ctrlpoint = 13;
        else Ctrlpoint = 15;
    }
    else                    //二车
    {
        if(speed_ave>1100)
            Ctrlpoint = 7;
        else if(speed_ave>850)
            Ctrlpoint = 10;
        else Ctrlpoint = 13;
    }
    if(m>Ctrlpoint)
        Ctrlpoint = m;

}
float  weight = 1 ;
uint8  wandao_flg = 0;
uint8 mm = 0;
void Cacl_Error() //加权取平均值
{
    Find_Crtlpoint();
    Least_Square_Method();
    Get_Curv();
    if(Xielv>0.8)
        wandao_flg = 1;
    else wandao_flg = 0;

    if(!start_finish_flg&&Start_Line_Overtake)
    {
       if(Car_State==QIAN) 
        {
             if(!chao_chedir)
             {
                mm = 46;
              } 
             else mm = 32;  //向左减小 向右增大 
         }

       else
          {
            if(!chao_chedir)
             {
                 mm = 31;
             }
            else mm = 47;
          }
     }
    else mm = 40;
    if(m<55)
    {
        float cnt = 0;
        for(uint8 i=ROW; i>=Ctrlpoint; i--)
        {
            if(i<=(uint8)(ROW+Ctrlpoint)/4) weight = 1;                     //最远处
            else if(i<=(uint8)(((ROW+Ctrlpoint)/4)*2))  weight = 1;
            else if(i<=(uint8)(((ROW+Ctrlpoint)/4)*3))  weight =1;
            else   weight = 1;                                            //最近处
            error += (Mid[i] - mm)*weight;
            cnt+=weight;
        }
        error = error/cnt;
        error = 0.5*error+0.5*error_last;
    }
    else
        error = error_last;
    error_last = error;
    error = error>50?50:error;
    error = error<-50?-50:error;
    derror = error - error_pre[3];

    for(uint8 i=0; i<3; i++)
    {
        error_pre[i] = error_pre[i+1];
    }
    error_pre[3] = error;

}