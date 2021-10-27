#include "getline.h"

uint8  findblackl(uint8 row,uint8 start,uint8 end)
{
    uint8 t =0;
    for(t=start; t<end; t++)
    {
        if(img[row][t-1]==WHITE&&img[row][t]==BLACK&&img[row][t+1]==BLACK)
            return t;

    }

    return 0;
}
uint8 findblackr(uint8 row,uint8 start,uint8 end)
{


    uint8 t =0;
    for(t=start; t<end; t++)
    {
        if(img[row][t-1]==BLACK&&img[row][t]==BLACK&&img[row][t+1]==WHITE)
            return t;

    }

    return 79;



}

uint8 findwhite(uint8 row ,int8 start, int8 end)
{
    for(int8 i = start; i<=end; i++)
        if(img[row][i] == WHITE)
        {
            return 1;

        }
    return 0;

}
uint8 findswhite(uint8 row ,int8 start, int8 end)
{
    for(int8 i = start; i>=end; i--)
        if(img[row][i] == WHITE)
        {
            return 1;

        }
    return 0;

}

uint8 findblack_lines(uint8 line,uint8 start, uint8 end )
{
    if(start > 59) start = 59;

    for(uint8 i = start; i>end; i--)
        if(img[i][line] == BLACK)
        {
            return  i;

        }
    return 0;


}
uint8 findwhite_line(uint8 line,uint8 start, uint8 end )
{
    for(uint8 i = start; i>end; i--)
        if(img[i][line] == WHITE)
        {
            return  i;

        }
    return 0;


}
uint8 findblack_line(uint8 line,uint8 start, uint8 end )
{
    for(uint8 i = start; i>end; i--)
        if(img[i][line] == BLACK)
        {
            return  i;

        }
    return 0;


}
uint8 findblack(uint8 row,uint8 start,uint8 end)
{
      for(int8 i = start; i<=end; i++)
        if(img[row][i] == BLACK)
        {
            return 0;

        }
    return 1;



}
int8  row =0;
int8 b_s = 0,b_e= 0 ,b_m = 0,r_f =0;
uint8  mid[80];
uint8 big_flg = 0;
uint8 round_endflg = 0;
uint8 round_rudder_flg = 0;
uint8 bb = 0;
uint8 out_flg = 0;
uint8 ee = 0;
int8 b1[60];
int8 b2[60];
uint8 near_row;
uint8 ss;
uint8 near_line;
int8 x_r = 0;
int8 x_l = 0;
uint8 tiaobiandian1 = 0;
uint8 tiaobiandian2 = 0;
uint8 x_1,x_2,x_3 = 0;
uint8 farst_row;
uint8 farst_line;
uint8 guai_flg;
uint8 guai_dian;
uint8 guai_row = 0;
uint8 r_f1= 0;
uint8 sround_start;
uint8 bround_start;
float xielv;
float xielv_1;
float xielv_2;  //变量为了调试方便 放在外边 后面可以放在里面
void out_round()
{

    uint8 kk = 0;
       for(uint8 i =15;i<=65;i++)
            {
                  if(abt(mid[i],mid[i+1])<=2)
          {
            kk = 1;
        }
        else
        {
            kk = 0 ;
            break;
        }
         }



    ee = 0;

    for(uint8 i = 59; i>0; i--)
    {
        if(img[i][40] == BLACK)
        {
            ee = i;
            break ;
        }
    }
    if(xielv>=0.2)
   {
   bb = 1;
   }
   else bb = 0;
    if(ee>10&&ee<55&&bb==1&&kk)
    {
        out_flg = 1;
        round_endflg = 1;
    }
    else
    {
        out_flg = 0;
        round_endflg = 0;
    }

    if(round_endflg==1)
    {
        for(uint8 i= 59; i>10; i--)
        {
            if(turn_flg == 1)
            {
                Right[r]=40+39*(i-ee)/(59-ee);
                if( Right[r]>79)   Right[r] = 79;
                if( Right[r]<0)   Right[r] = 0;
                r--;
            }
            else
            {
                Left[l] = 40+40*(i-ee)/(ee-59);
                if( Left[l]<0)  Left[l] = 0;
                if( Left[l]>79)  Left[l] = 79;
                l--;
            }
        }
    }         
   
}
uint8 findmax(int8 a[],uint8 start,uint8 end )
{
  uint8 max = 0; 
  for(uint8 i = start; i>end; i--)
    {
        if(a[i]>=max)
           max= a[i]  ;
  }
 return max;
}
uint8 findmin(int8 a[],uint8 start,uint8 end)
{
  uint8 min = 79; 
  for(uint8 i = start; i>end; i--)
    {
        if(a[i]<=min)
           min= a[i]  ;
  }
 return min;

}
uint8 order_increase(int8 a[],uint8 start,uint8 end)
{
    for(uint8 i = start; i>end+1; i--)
    {
        if(a[i]<=a[i-1])
            continue;
        else return 0;
    }

    return  1;
}
uint8 order_decrease(int8 a[],uint8 start,uint8 end)
{
    for(uint8 i = start; i>end+1; i--)
    {
        if(a[i]>=a[i-1])
            continue;
        else return 0;
    }
    return  1;
}
uint8 equal_num(int8 a[],uint8 start,uint8 end)
{
    uint8 val = 0;
    for(uint8 i = start; i<end-1; i++)
    {
        if(a[i]==a[i+1]) val++;
        else return val;
    }
    return val;
}
void findround()
{
    if(r<=0) r=0;
    if(l<=0) l=0;
    x_r = 0;
    x_l = 0;
    r_f1= 0;
    
    b_s = findblack_line(40,59,0);  //找40列的黑点
    b_e = findwhite_line(40,b_s,0); //找40列的黑点的结束行
    b_m = b_s -2;
    r_f = findwhite(b_s,40,79);
    guai_flg = 0;
/****************** 找拐点,只找一边 两边都有则说明 车身比较正（此时另外识别小环岛）******/ 
    if(l==59&&r!=59) 
       {


          guai_dian = 79;
          guai_row = 0;
        for(uint8 i = 59;i>=r;i--)
           {
             if(guai_dian>=Right[i])
                  {
                   guai_dian = Right[i];
                   guai_row = i;
                  }
            }
        for(uint8 i = guai_row;i<58;i++)
           {
            if(Right[i]<=Right[i+1]) guai_flg = 1;
            else 
                {
                 guai_flg = 0;
                  break;
                 }
           }

        for(uint8 i = guai_row;i>r+2;i--)
          {

           if(Right[i]<=Right[i-1]) guai_flg = 1;
            else 
                {
                 guai_flg = 0;
                  break;
                 }
             }
        if(guai_row==r) guai_flg = 0;
      
       }
    else if(r==59&&l!=59)
        {
               guai_dian = 0;
               guai_row = 0;
               for(uint8 i = 59;i>l;i--)
           {
             if(guai_dian<=Left[i])
                  {
                   guai_dian = Left[i];
                   guai_row = i;
                  }
            }
            for(uint8 i = guai_row;i<58;i++)
           {
            if(Left[i]>=Left[i+1]) guai_flg = 1;
            else 
                {
                 guai_flg = 0;
                  break;
                 }
           }
              
        for(uint8 i = guai_row;i>l+1;i--)
          {

           if(Left[i]>=Left[i-1])  guai_flg = 1;
            else 
                {
                 guai_flg = 0;
                  break;
                 }
             }
          if(guai_row==l) guai_flg = 0;
         }
    else 
    {
     guai_dian = 79;
     guai_flg = 0;

    }
/*****************end********************************************************************/    
//判断黑点中点行左边是否有白点
    /*r_f &= findwhite(b_m,40,78);     //判断黑点中点行右边是否有白点
    r_f &= findswhite(b_s,40,1);    //判断黑点的结束行左边是否有白点
    r_f &= findwhite(b_s,40,78);    //判断黑点的结束行右边是否有白点
    r_f &= findwhite(b_e+2,40,78);    //判断黑点的结束行右边是否有白点
    r_f &= findswhite(b_e+2,40,1);
    r_f &= findswhite(b_e,40,1);    //判断黑点的开始行左边是否有白点
    r_f &= findwhite(b_e,40,78);*/
/*                    按列扫描存储黑点轮廓                                     */
    for(uint8 i = 0; i<80; i++)
    {
        mid[i] = 79; //初始化mid数组 用来存黑点的轮廓
    }

    for(int8 i= 0; i<=79; i++)
    {
        mid[i] = findblack_lines(i,59,0); //找到每一行离车最近的黑点
    }
/*                 end                                                        */




/*                       确定离车最近 最远 的黑点的位置 被线提到的黑点 不算       */
    near_row = 0;
    farst_row = 0;
    near_line = 0;
    farst_line = 0;
    uint8 sta = 0;
    uint8 ed = 0;
    if(r==59&&l!=59) 
     {
       sta = guai_dian;
       ed = 76;
     }
    else if (l==59&&r!=59)
    {
         sta = 3;
         ed = guai_dian;

    }
    else if(l==59&&r==59)
    {
         sta = 3;
         ed = 76;
     }

    for(uint8 i = sta+1; i<ed; i++)
    {
        if(mid[i]>near_row)
        {
            near_row = mid[i];
            near_line = i;
        }
    }
 
   for(uint8 i = near_row;i>1;i--)
   {
     
     if(img[i][near_line]==WHITE)
     {
      farst_row = i+1;
      farst_line = near_line;
      break;
     }
   }
/*                        end                                               */
/*                    黑点连续性判断                                         */
    for(uint8 i = 15; i<65; i++)
    {
        if(abt(mid[i],near_row)<=5)
        {
            ss = 1;
        }
        else
        {
            ss = 0 ;
            break;
        }
    }
/*                        end                                               */

/*                         找一行的半边是否全黑                             */
       for(uint8 i = near_row; i>=farst_row&&near_row!=0&&farst_row!=0; i--)         
    {

        if(findwhite(i,near_line,79)==0) x_r++;
        if(findswhite(i,near_line,0)==0) x_l++;
//        r_f &= findwhite(i,40,79);     //判断黑点中点行右边是否有白点
//        r_f &= findswhite(i,40,0);
    }
 

/*                                end                                      */   
   
/*                     以行为单位存储黑点的轮廓                            */    
    
     for(int8 i = 59; i>=0; i--)
    {
        b1[i] = findblackl(i,1,near_line+1);    //左边
        b2[i] = findblackr(i,near_line-1,78);   //右边
    }


/*                        end                                               */

/*                        算两条交叉线的斜率 出环岛以及大环岛的识别         */
    xielv_1 = 0;
    uint8 k = 0;
    for(uint8 j =near_row-2;j>farst_row+1;j--)
   {
      if(b1[j]==0||(b1[j]<=b1[j-1])) 
      {
       k = near_row-2-j;
       break;
      }
      else 
      {
       k = near_row-2-j;

      }
      xielv_1 += (float)(b1[near_row-1]-b1[j])/(near_row-j-1);
   }
   if(xielv_1 != 0)
     {
                xielv_1 /= k ;
                xielv_1 = 1/xielv_1;
     }
   xielv_2 = 0;
   for(uint8 j =near_row-2;j>farst_row+1;j--)
     {
       if(b2[j]==79||(b2[j]>=b2[j-1])) 
      {
       k = near_row-2-j;
       break;
      }
      else 
      {
       k = near_row-2-j;

      }
      xielv_2 += (float)(b2[near_row-1]-b2[j])/(near_row-j-1);


      }
    if(xielv_2!= 0)
     {
                xielv_2 /= k;
               xielv_2 = 1/xielv_2;
     }

    xielv = ufabs(xielv_1-xielv_2);

/*                        end                                               */


/*                  车身不正进入环岛的判断                                 */
   if(x_r!=0&&x_l==0)
  {    
       tiaobiandian1 = 0;
       tiaobiandian2 = 0;
        for(uint8 i = near_row; i>farst_row+1; i--)
        {
            if(b2[i]!=79&&tiaobiandian1==0)
            {
                continue;
            }
            else if(b2[i]==79&&tiaobiandian1==0)
            {
                tiaobiandian1 =i;
            }
            else if(b2[i]==79&&tiaobiandian1!=0&&b2[i-1]==79)
            {
                continue;
            }
            else if(b2[i]==79&&tiaobiandian1!=0&&b2[i-1]!=79)
            {
                tiaobiandian2 = i;
                break;
            }
        }
       x_1 = 0;
       x_2 = 0;
       x_3 = 0;
        if(tiaobiandian2==0)   { r_f1 =0 ;goto here;}
        uint8 wide = 0;
        wide =79-findmin(b1,tiaobiandian1,tiaobiandian2);
        x_1 =order_increase(b2,near_row,tiaobiandian2);
        x_2 =equal_num(b2,tiaobiandian2,tiaobiandian1);
        x_3 =order_decrease(b2,tiaobiandian2+1,farst_row+1);
        uint8 pp = abt(x_2,x_r);
        if(x_1&&(tiaobiandian2!=0)&&(pp<10)&&x_3&&wide<60&&wide>=40)
        {
            r_f1 = 1;
        }
        else r_f1 = 0;
        if(r_f1==0) goto here;
        
         tiaobiandian1 = 79;
         tiaobiandian2 = 79;
        for(uint8 i = near_row; i>farst_row; i--)
        {
            if(b1[i]>=b1[i-1]&&tiaobiandian1==79)
            {
                continue;
            }
            else if(b1[i]<=b1[i-1]&&tiaobiandian1==79)
            {
                tiaobiandian1 = i+1;
                break;
            }
         }
       x_1 = 0;
       x_2 = 0;
       x_3 = 0;
       if(tiaobiandian1==79)  { r_f1 =0 ;goto here;}
        x_1 =order_decrease(b1,near_row,tiaobiandian1);
      //  x_2 =equal_num(b1,tiaobiandian2,tiaobiandian1);
        x_3 =order_increase(b1,tiaobiandian1,farst_row);
        if(x_1&&x_3)
        {
            r_f1 = 1;
        }
        else r_f1 = 0;
    }
     else if(x_l!=0&&x_r==0)    
      {  
        
        tiaobiandian1 = 79;
         tiaobiandian2 = 79;
        for(uint8 i = near_row; i>farst_row+1; i--)
        {
            if(b1[i]!=0&&tiaobiandian1==79)
            {
                continue;
            }
            else if(b1[i]==0&&tiaobiandian1==79)
            {
                tiaobiandian1 = i+1;
            }
            else if(b1[i]==0&&tiaobiandian1!=79&&b1[i-1]==0)
            {
                continue;
            }
            else if(b1[i]==0&&tiaobiandian1!=79&&b1[i-1]!=0)
            {
                tiaobiandian2 = i;
                break;
            }

        }
       x_1 = 0;
       x_2 = 0;
       x_3 = 0;
       uint8 wide = 0;
       if(tiaobiandian2>=59)  { r_f1 =0 ;goto here;}
        wide = findmax(b2,tiaobiandian1,tiaobiandian2);
        x_1 =order_decrease(b1,near_row,tiaobiandian2);
        x_2 =equal_num(b1,tiaobiandian2,tiaobiandian1);
        x_3 =order_increase(b1,tiaobiandian2+1,farst_row+1);
        if(x_1&&(abt(x_2,x_l)<10)&&x_3&&(tiaobiandian2!=0)&&wide<60&&wide>=40)
        {
            r_f1 = 1;
        }
        else r_f1 = 0;
       if(r_f1==0) goto here;
         tiaobiandian1 = 0;
         tiaobiandian2 = 0;
        for(uint8 i = near_row; i>farst_row+1; i--)
        {
            if(b2[i]<=b2[i-1]&&tiaobiandian1==0)
            {
                continue;
            }
            else if(b2[i]>=b2[i-1]&&tiaobiandian1==0)
            {
                tiaobiandian1 =i;
            }
    
        }
       x_1 = 0;
       x_2 = 0;
       x_3 = 0;
      if(tiaobiandian1==0)  { r_f1 =0 ;goto here;}
        x_1 =order_increase(b2,near_row,tiaobiandian1);
     //   x_2 =equal_num(b2,tiaobiandian2,tiaobiandian1);
        x_3 =order_decrease(b2,tiaobiandian1,farst_row+1);
        uint8 pp = abt(x_2,x_r);
        if(x_1&&x_3)
        {
            r_f1 = 1;
        }
        else r_f1 = 0;
       

   }
   else if(x_r!=0&&x_l!=0) r_f1 = 0;
   //if((xielv>0.7||xielv==0)&&r_f1==1)  r_f1=0;  

/*                        end                                               */
here:  
/*           车身正的时候进入环岛时小环岛的判断                             */   
   for(uint8 i = b_s;i>b_e+2;i--)
       {
       r_f &= findwhite(i,40,79);     //判断黑点中点行右边是否有白点
       r_f &= findswhite(i,40,0);
       }
/*                        end                                               */    
/*                             大环岛判断                                     */
   

   uint8 xielv_flg = 0;
    if(ss)
      {
     if(xielv<=0.9&&xielv!=0)//&&b_s != 0&&(b_s-b_e)>=15&&b_s<55&&b_s>12)
      {
             xielv_flg = 1; 
      }
    else xielv_flg = 0;
    }
    else if(!ss)
     {      

          uint8 jj = 0;  
           for(uint8 i =5;i<=75;i++)
            {
                  if(abt(mid[i],mid[i+1])<=3)
          {
            jj = 1;
        }
        else
        {
            jj = 0 ;
            break;
        }
         }
        
         if((xielv_1!=0&&xielv_2==0&&jj&&xielv<0.3&&xielv>=0.22)||(xielv_1==0&&xielv_2!=0&&jj&&xielv<0.3&&xielv>=0.22))
        {
           xielv_flg  = 1;
 
        } 
         else xielv_flg = 0;
    }
 
  

   
    if(xielv_flg&&b_s != 0&&(b_s-b_e)>=15&&b_s<55&&b_s>12&&!r_f&&!r_f1&&!sround_start)  
      big_flg = 1;
    else big_flg = 0;
/*                        end                                               */  
 
   if(Round_Overtake_Enable)
   {
         if((flag==13||flag==14)&&Car_State==HOU)
            {
                if(b_s>15&&b_s<50)  big_flg = 1;
            }
        if(Car_State==HOU)
            {
                if(flag ==9||flag==13)
                    turn_flg = 0;
                else if(flag==10||flag==14) turn_flg = 1;
            }
   }

    /***********************************end****************************************/
    if(l==5&&r==5)                          //防止后车误判 
        {
         r_f  = 0;
         r_f1 = 0;
        }
 /*  if((r_f1 == 1&& near_row != 0 && farst_row!= 0&&(near_row-farst_row)>=10&&near_row<55&&near_row>12))
    {
        roundspeed_flg = 0;
    }
    else */ 
  if((r_f == 1&& b_s != 0 && b_e!= 0&&(b_s-b_e)>=15&&b_s<55&&b_s>12))
    {
         roundspeed_flg = 1;
    }
    else 
    {
        roundspeed_flg = 0;
    }
    /**************小环岛 前车 停车 干扰后车 放宽检测 条件*************************/
    if(Round_Overtake_Enable)
    {
        if(Car_State==HOU&&(flag==10||flag==9)&&big_flg!=1)
      {
          
            r_f = findswhite(b_s,40,0);    //判断黑点的结束行左边是否有白点
            r_f &= findwhite(b_s,40,79);    //判断黑点的结束行右边是否有白点
            r_f &= findwhite(b_s-2,40,79);    //判断黑点的结束行右边是否有白点
            r_f &= findswhite(b_s-2,40,0);
            if(b_s>55&&b_s<10) r_f = 0;
            else  
            {
             r_f&=findblack(b_s+5,0,79);
             }
            if(r_f == 1&& b_s != 0 && b_e != 0&&(b_s-b_e)>=15&&b_s>12)
            {
                roundspeed_flg = 1;
            }
            else
            {
                roundspeed_flg = 0;
            }
      }
    }
   else 
   {
       if(Car_State==HOU&&big_flg!=1&&flag==99)
      {
          
            r_f = findswhite(b_s,40,0);    //判断黑点的结束行左边是否有白点
            r_f &= findwhite(b_s,40,79);    //判断黑点的结束行右边是否有白点
            r_f &= findwhite(b_s-2,40,79);    //判断黑点的结束行右边是否有白点
            r_f &= findswhite(b_s-2,40,0);
          
            if(r_f == 1&& b_s != 0 && b_e != 0&&(b_s-b_e)>=15&&b_s>12)
            {
                roundspeed_flg = 1;
            }
            else
            {
                roundspeed_flg = 0;
            }
      
      } 
   }

    /*******************************end*******************************************/
     
     if(roundspeed_flg!=1&&l==59&&r==59&&big_flg!=1&&(bround_start||sround_start))   out_round();
    else out_flg = 0;


    row = b_s;

    /************************小环岛排除bug******************************************/
    if(roundspeed_flg==1&&big_flg!=1)
    {
        uint8 oo = 0;
        if(l!=59&&r==59)
            for(uint8 i = 59; i>l; i--)
            {
                if(Left[i]==0)
                    oo++;
            }
        if(oo>40||l>50)
        {
            l = 59;
            for(uint8 i = 0; i<60; i++)
            {
                Left[i] = 0;
            }
        }
        oo = 0;
        if(r!=59&&l==59)
        {
            for(uint8 i = 59; i>r; i--)
            {
                if(Right[i]==79)
                    oo++;
            }
        }
        if(oo>40||r>50)
        {
            r =59;
            for(uint8 i = 0; i<60; i++)
            {
                Right[i] = 79;
            }
        }
    }

    /********************************end*******************************************/ 
//   if((flag==13||flag==14)&&Car_State==HOU)
//    {
//        if(b_s>15&&b_s<50)  big_flg = 1;
//    }
    if(((big_flg==1)||(roundspeed_flg==1))&&l==59&&r==59)
    {
        round_flg = 1;
    }
    else round_flg = 0;

    /**********************小环岛超车排除后车的提线问题****************************/

    if(Round_Overtake_Enable&&Car_State==HOU&&(flag==10||flag==9)&&big_flg!=1)
    {
        if(flag ==9&&roundspeed_flg&&r==59)
        {
            if(b_s<50&&b_s>20)//&&b_e!=0)
            {
                l = 59;
                round_flg = 1;
                for(uint8 i = 0; i<60; i++)
                {
                    Left[i] = 0;
                }
            }


        }
        else if(flag ==10&&roundspeed_flg&&l==59)
        {
            if(b_s<50&&b_s>20&&b_e!=0)
            {
                r = 59;
                round_flg = 1;
                for(uint8 i = 0; i<60; i++)
                {
                    Right[i] = 79;
                }
            }


        }

    }
    /*************************************end**************************************/
    if(round_flg==1&&!big_flg)
    {
       sround_start = 1;

    }
    else if(round_flg==1&&big_flg)
    {

    bround_start = 1;
 
    }




    if(round_flg == 1)
    {
        /************************** 环岛超车代码***************************************/
        if(Round_Overtake_Enable)          //环岛超车使能
        {
            if(Car_State==QIAN)
            {
                turn_flg = overtakedir[chao_checishu];
                if(big_flg!=1)
                {
                    if(turn_flg==0)
                    {
                        uint8 testflag = 10;
                        car_send(TYPE_FLAG,&testflag);
                        car_send(TYPE_FLAG,&testflag); //前车发现环岛 告诉后车超车
                    }
                    else if(turn_flg)
                    {
                        uint8 testflag = 9;
                        car_send(TYPE_FLAG,&testflag);
                        car_send(TYPE_FLAG,&testflag); //前车发现环岛 告诉后车超车

                    }
                }
                else
                {
                    if(turn_flg==0)
                    {
                        uint8 testflag = 14;
                        car_send(TYPE_FLAG,&testflag);
                        car_send(TYPE_FLAG,&testflag); //前车发现环岛 告诉后车超车
                    }
                    else if(turn_flg)
                    {
                        uint8 testflag =13 ;
                        car_send(TYPE_FLAG,&testflag);
                        car_send(TYPE_FLAG,&testflag); //前车发现环岛 告诉后车超车
                    }



                }
            }
            if(Car_State==HOU)
            {
                if(flag ==9||flag==13)
                    turn_flg = 0;
                else if(flag==10||flag==14) turn_flg = 1;

            }
        }
        else 
        {
                if(Car_State==QIAN)
              {
                 
                if(big_flg!=1)
                {
                   
                        uint8 testflag = 99;
                        car_send(TYPE_FLAG,&testflag);
                        car_send(TYPE_FLAG,&testflag); //前车发现环岛 告诉后车超车
                 
                }
                else 
                {
                     uint8 testflag = 100;
                        car_send(TYPE_FLAG,&testflag);
                        car_send(TYPE_FLAG,&testflag); //前车发现环岛 告诉后车超车
                
                
                }
              }
        
        
        }

        /******环岛超车代码结束********************************************************/
        round_rudder_flg = 1;

        for(int8 i= 59; i>10; i--)
        {
            if(turn_flg == 1)
            {
                Right[r]=(40+39*(i-row)/(59-row));
                if( Right[r]>79)   Right[r] = 79;
                if( Right[r]<0)   Right[r] = 0;
                r--;
            }
            else
            {
                Left[l] = (40+40*(i-row)/(row-59));
                if( Left[l]<0)  Left[i] = 0;
                if( Left[l]>79)  Left[i] = 79;
                l--;
            }
        }
    }
    else
    {
        round_rudder_flg = 0;
    }
}

