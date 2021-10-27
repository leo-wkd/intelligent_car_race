#include "getline.h"

uint8 r,l,m;
int8 Mid[ROW+1];
int16 Left[ROW+1];
int16 Right[ROW+1];


uint8 LaststartpointL=15;//预设左边点
uint8 LaststartpointR=65;//预设右边点
uint8 Length1[ROW+1] =  //风驰赛道每一行的宽度
{
    9,14,17,16,18,
    28,27,27,29,32,
    34,34,35,37,37,
    39,40,41,43,44,
    45,46,47,49,49,
    51,52,53,54,55,
    56,57,59,59,61,
    61,63,64,65,66,
    68,68,69,70,70,
    71,72,73,74,75,
    77,78,78,79,79,
    79,79,79,79,79,
};
uint8 Length2[ROW+1] =  //  电掣赛道每一行的宽度
{
    9,14,15,16,18,
    22,24,26,28,29,
    30,32,33,34,36,
    36,38,39,40,41,
    42,43,45,45,47,
    48,48,50,51,52,
    54,54,55,56,57,
    58,59,61,61,63,
    63,64,65,65,67,
    68,69,70,71,72,
    73,74,75,76,76,
    78,78,79,79,79,
};
uint8 L1[80] = {0};




//-----提取基准线----//
uint8 startflg;
uint8 Get_start_range_L = 10;
uint8 Get_start_range_R = 10;
void getstart()
{
    startflg = 0;//ff 左右找到，f0左找到，0f右找到
    uint8 BlackRt[3] = {LINE};//右边三个跳变点位置
    uint8 BlackLt[3] = {0};//左边三个跳变点位置

    BlackLt[0]=getL(59,LaststartpointL,15);
    BlackLt[1]=getL(58,BlackLt[0],5);
    BlackLt[2]=getL(56,BlackLt[1],5);

    BlackRt[0]=getR(59,LaststartpointR,15);
    BlackRt[1]=getR(58,BlackRt[0],5);
    BlackRt[2]=getR(56,BlackRt[1],5);

    //判断是否找到左右线
    if((BlackLt[0]!=0)&&(BlackLt[1]!=0)&&(BlackLt[2]!=0))
    {
        startflg |= 0xf0;			//左找到
        Left[ROW]=BlackLt[0];
    }
    if((BlackRt[0]!=LINE)&&(BlackRt[1]!=LINE)&&(BlackRt[2]!=LINE))
    {
        startflg |= 0x0f;			//右找到
        Right[ROW]=BlackRt[0];
    }
}

//-----priority(优先级)	1:两边都找到	2:一边找到	3:两边都没有找到
uint8 Judge_Priority(uint8 i)
{
    if(Left[i]!=0 && Right[i]!=LINE)	return 1;
    else if(Left[i]==0 && Right[i]==LINE)	return 3;
    else									return 2;
}

/****************************************/
//
//			//-----计算中线-----//
//
/****************************************/
void getmiddleline()
{

    //两边都没找到
    if(l==ROW && r==ROW)
    {
        Mid[ROW] = 40;
        return;
    }
    //求中线
    if(double_car_flg == 1)
    {
        for(m=ROW; m>=(l>r?l:r); m--)
        {
            if(Left[m]!=0 && Right[m]==LINE)
                Mid[m] = Left[m] + Length1[m]/2;
            else if(Left[m]==0 && Right[m]!=LINE)
                Mid[m] = Right[m] - Length1[m]/2;
            else
                Mid[m] = (Left[m]+Right[m]+1)/2;
        }
        for(; m>=(l<r?l:r); m--)
        {
            if(l<r)
            {
                Mid[m] = Left[m] + Length1[m]/2;
            }
            else if(l>=r)
            {
                Mid[m] = Right[m] - Length1[m]/2;
            }
        }
    }
    else
    {

        for(m=ROW; m>=(l>r?l:r); m--)
        {
            if(Left[m]!=0 && Right[m]==LINE)
                Mid[m] = Left[m] + Length2[m]/2;
            else if(Left[m]==0 && Right[m]!=LINE)
                Mid[m] = Right[m] - Length2[m]/2;
            else
                Mid[m] = (Left[m]+Right[m]+1)/2;
        }
        for(; m>=(l<r?l:r); m--)
        {
            if(l<r)
            {
                Mid[m] = Left[m] + Length2[m]/2;
            }
            else if(l>=r)
            {
                Mid[m] = Right[m] - Length2[m]/2;
            }
        }


    }
    //判断第ROW行优先级
    uint8 priority = Judge_Priority(ROW);
    //分段平移
    for(uint8 i=ROW-1; i>=(l<r?l:r); i--)
    {
        uint8 priority_temp = Judge_Priority(i);
        if(priority_temp != priority)
        {
            if(priority_temp<priority)//远的一行的优先级高
            {
                int8 correct_num = Mid[i]-Mid[i+1];
                for(uint8 j=ROW; j>i; j--)
                {
                    Mid[j] += correct_num;
                }
            }
            else//近的一行优先级高
            {
                //向前搜索优先级不一样的点
                uint8 k=i;
                for(; k>=(l<r?l:r); k--)
                {
                    uint8 priority_temp_1 = Judge_Priority(k);
                    if(priority_temp_1 != priority_temp)
                    {
                        break;
                    }
                }
                int8 correct_num = Mid[i]-Mid[i+1];
                for(; i>k; i--)
                {
                    Mid[i] -= correct_num;
                }
                i++;
            }
        }
        priority = 	priority_temp;
    }

    //-------------滤波，消除锯齿状波形---------------//
    for(uint8 i = ROW-2; i>=m&&i>=END; i--) //对中线进行滤波，使其光滑
    {
        if((Mid[i+2] == Mid[i+1])&&(Mid[i+1] == Mid[i]))//3个连续的点在同一列
        {
            uint8 m0 = Mid[i];
            for(uint8 j = i-1; j>m&&j>=END; j--) //向后查找列数是m的行
            {
                if(Mid[j] == m0)		i = j;
                else break;
            }

            uint8 m1,m2,m3;
            m1 = Mid[i-1];
            m2 = Mid[i-2];
            m3 = Mid[i-3];

            if((m1==m0+1&&m2==m1-1)||(m1==m0-1&&m2==m1+1))	Mid[i-1] = m0;
            if(m1==m0+1&&m1==m2&&m3==m2-1)					Mid[i-1] = m0,Mid[i-2] = m0;
            if(m1==m0+1&&m1==m2+1&&m3==m2-1)				Mid[i-2] = Mid[i-1];

            if(m1==m0-1&&m1==m2&&m3==m2+1)					Mid[i-1] = m0,Mid[i-2] = m0;
            if(m1==m0-1&&m1==m2-1&&m3==m2+1)				Mid[i-2] = Mid[i-1];
        }
    }

    //-----滤波，使中线光滑-----//

    for(uint8 i = 0; i<l; i++)	Left[i] = 0;
    for(uint8 i = 0; i<r; i++)	Right[i] = LINE;

    if(m<(l<r?l:r)) m = (l<r?l:r);
}


//-----普通提线，不处理十字----//
void getline()
{
    l=ROW;
    m=ROW;
    r=ROW;

    for(uint8 i = 0; i<=ROW; i++) //初始化行，列坐标
    {
        Left[i] = 0;
        Right[i] = LINE;
        Mid[i] = 40;
    }
    //查找起跑线
    getstart();
    //-----边缘提线-----//
    if(startflg == 0x00)//起始两边都没有找到
    {
        Find_Left_Line();
        Find_Right_Line();
    }
    else if(startflg == 0x0f)//起始只找到了右边
    {
        Handle_Right_Line();
        Find_Left_Line();
//		Get_start_range_L = 20;
//		Get_start_range_R = 10;
    }
    else if(startflg == 0xf0)//起始只找到了左边
    {
        Handle_Left_Line();
        Find_Right_Line();
    }
    else					//起始两边都找到
    {
        Handle_Left_Line();
        Handle_Right_Line();
    }
}
/****************************************/
//
//			//-----消除切外道时反光造成的影响-----//
//
/****************************************/
void Check_Error()
{
    if(Left[l]>=76)
    {
        if(r<=l)
        {
            r = ROW;
        }
        for(uint8 i=ROW; i>=(l<r?l:r); i--)
        {
            if(Left[i]>Right[i])
            {
                r = ROW;
                break;
            }
        }
        if(l>=40)
        {
            if(r!=ROW)
            {
                r = ROW;
            }
        }
    }
    if(Right[r]<=3)
    {
        if(l<=r)
        {
            l = ROW;
        }
        for(uint8 i=ROW; i>=(l<r?l:r); i--)
        {
            if(Left[i]>Right[i])
            {
                l = ROW;
                break;
            }
        }
        if(r>=40)
        {
            if(l!=ROW)
            {
                l = ROW;
            }
        }
    }
}

/****************************************/
//
//			//-----提线程序入口-----//
//
/****************************************/
uint8 css = 0;
unsigned char round_flg = 0;
uint8 turn_flg = 0;
uint8 error_flg = 1;
uint8 Slope_flg = 0;
uint16 wide = 0;
void Find_Slope()
{

    uint8 i= 0;
    for(i= 59; i>=m; i--)
    {
        wide+= Right[i]-Left[i];

    }
    wide = wide/(59-m+1);
    if(wide>=63&&l<10&&r<10)
        Slope_flg = 1;
    else Slope_flg = 0;
    wide = 0;
}
uint8 GetLine_Error_flg = 0;
uint8 start_finish_flg = 0;
void GetLine()
{
    getline();

    //-----处理十字-----//
    Find_Cross();
    if(cross_flg == 0)
    {
         // Fix_Blank();
    }
     findround();
    //左边线大于右边线，是在切外道时，反光导致
    for(uint8 i=ROW; i>=(l<r?l:r); i--)
    {
        if(Left[i]>Right[i])
        {
            GetLine_Error_flg = 1;
            break;
        }
        if(i == (l<r?l:r))
            GetLine_Error_flg = 0;
    }
    if(GetLine_Error_flg == 1&&round_flg!=1)
    {
        l = ROW;
        r = ROW;
    }

    Check_Error();
    if(Double_Car_Mode)
       get_startline();
    if(Start_Line_Overtake)
    {
      if(Car_State==QIAN)
      {
       if(!start_finish_flg)
       {
        if(!chao_chedir)
        {
              for(uint8 i = 59;i>5;i--)
                  {
                   Left[i] = 40;
                  }
            l =5;
         }
         else
         {
              for(uint8 i = 59;i>5;i--)
            {
                Right[i] = 40;
                }
           r= 5;
        }
        }
      }
      else if(Car_State==HOU)
      {
      if(!start_finish_flg)
       {
         if(chao_chedir)
        {
              for(uint8 i = 59;i>5;i--)
                  {
                   Left[i] = 40;
                  }
            l =5;
         }
         else 
        { 
            for(uint8 i = 59;i>5;i--)
            {
             Right[i] = 40;
            }
            r= 5;
       }
        }
       }
    
     }
    if(Slope_distance==0)
    findzhangai();

  
    //-----计算中线-----//

    getmiddleline();
    Find_Slope();
    for(uint8 i = 0; i<60; i++)
    {
        L1[i] = Right[i]-Left[i];


    }
    //-----记录起跑线-----//
    if(r<=55)	LaststartpointR = Right[55];
    else
    {
        if(r==ROW && Right[r]==LINE);
        else 	LaststartpointR = Right[ROW];
    }
    if(l<=55)	LaststartpointL = Left[55];
    else
    {
        if(l==ROW && Left[l]==0);
        else	LaststartpointL = Left[ROW];
    }
}

