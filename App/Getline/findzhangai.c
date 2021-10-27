#include "getline.h"
uint8 zhangai_left;
uint8 zhangai_rows;
uint8 zhangai_right;
uint8 zhangai_rowe;
uint8 tiao1 = 0;
uint8 tiao2 = 0;
uint8 tiao = 0;
uint8 zhang_s;
uint8 zhang_e;
void findzhangai(void)
{

   tiao = 0;
   tiao1 = 0;
   tiao2 = 0;
   zhang_e = 0;
   zhang_s = 0;
   for(uint8 i = 59;i>l;i--) 
   {
   for(uint8 j = 40;j>Left[i]+1;j--)
   {
      if(img[i][j]==WHITE&&img[i][j-1]==BLACK&&tiao1==0)
           {
             tiao1 += 1;
            }
        if(img[i][j]==BLACK&&img[i][j-1]==WHITE&&tiao1!=0)
           {
             tiao2 += 1;
           }
    }      
//   if(tiao==0&&) 
        if(tiao1==1&&tiao2==1)
          {
             tiao++;
          }
        else  if(tiao1>1||tiao2>1)
          {
            zhangai_left = 0;  
            break;
          } 
          if(tiao==1)
          {
           zhang_s = i;
          }
         if(tiao1==1&&tiao2==1&&tiao>=10)
         {
            zhangai_left = 1;
            zhang_e = i;
            break;
         }
         else if(tiao>0&&tiao1!=1&&!tiao2!=1)
         {
            zhangai_left = 0;
            break;
         }
         tiao1 = 0;
         tiao2 = 0;
   }
         tiao1 = 0;
         tiao2 = 0;
         tiao = 0;
   
   for(uint8 i = 59;i>r;i--)
     {
        for(uint8 j = 40;j<Right[i]-1;j++)
     {
      if(img[i][j]==WHITE&&img[i][j+1]==BLACK&&tiao1==0)
           {
             tiao1 += 1;
            }
        if(img[i][j]==BLACK&&img[i][j+1]==WHITE&&tiao1!=0)
           {
             tiao2 += 1;
           }
    } 
         if(tiao1>1||tiao2>1)
           {
             zhangai_right = 0;  
             break;
           } 
        
        if(tiao1==1&&tiao2==1)
          {
             tiao++;
          }
       else if(tiao1>1||tiao2>1)
           {
             zhangai_right = 0;  
             break;
           } 
          if(tiao==1)
          {
           zhang_s = i;
          }
         if(tiao1==1&&tiao2==1&&tiao>=10)
         {
            zhangai_right = 1;
            zhang_e = i;
            break;
         }
         else if(tiao>0&&tiao1!=1&&!tiao2!=1)
         {
            zhangai_right = 0;
            break;
         }
         tiao1 = 0;
         tiao2 = 0;

     }
   if(zhangai_left||zhangai_right)
   {
    for(uint8 i = 59;i>=zhang_e;i--)
    {
    if(img[i][40]==BLACK) 
     {
      zhangai_left = 0;
      zhangai_right = 0;
      break;
     }
 
    }
  }
    if(zhangai_left==1&&zhang_s>20&&!zhangai_right)
    {
  
     for(uint8 i =59;i>l;i--)
     {
          Left[i] = 40;
      }
   }
    else if(!zhangai_left&&zhang_s>20&&zhangai_right)
   {
      for(uint8 i =59;i>r;i--)
     {

        Right[i] = 40;
      }

   }
 

}  

    /* findwhite_line(uint8 line,uint8 start, uint8 end )*/

  /* for(uint8 i=40;i<79;i++)
   { ]
      if(uabs8(hei[i]-hei[i+1])>20)
        {
         zhangai_rows = hei[i+1];
         zhangai_right = i+1;
         break;
        }
   }
   if(zhangai_left!=0)
   zhangai_rowe = findwhite_line(zhangai_left,zhangai_rows,0);
   else 
   zhangai_rowe = findwhite_line( zhangai_right,zhangai_rows,0);
   if(zhangai_rows>25&&zhangai_left!=0) 
   for(uint8 i = 59;i>5;i--)
      {
      Left[i] = 40;
      }
   else if(zhangai_rows>25&&zhangai_right!=0)
      {
      for(uint8 i = 59;i>5;i--)
      {
      Right[i] = 40;
      }

      }
   */
