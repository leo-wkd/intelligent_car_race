#include "getline.h"


//-----扫描左边沿，一个方向-----//
uint8 getLs(uint8 Lrow,uint8 Lline,uint8 np)
{
    uint8 Lstart = 0,Lend = 0;//Lstart>Lend
    //限制Lline的值在0-79之间
    //限制Lrow的值在0-59之间
    if(Lline>LINE+50) Lline = 0;
    if(Lline>LINE&&Lline<=LINE+50) Lline = LINE;
    if(Lrow>ROW+50) Lrow = 0;
    if(Lrow>ROW&&Lrow<=ROW+50) Lrow = ROW;
    //限制Lstart的值在0-77之间
    //限制Lend的值在2-79之间
    if((Lline+np)>RBP)	Lstart=RBP;
    else	Lstart=Lline+np;
    if((Lline)<(LBP+np))	Lend=LBP;
    else	Lend=Lline-np;
    //限制Lline的值在2-77之间
    if(Lline>RBP)	Lline = RBP;
    if(Lline<LBP)	Lline = LBP;
    //限制t的值在2-79之间
    for(uint8 t=Lstart+2; t>=Lend; t--) //扫描方式<---||<---
    {
        if((img[Lrow][t-2] == BLACK)&&(img[Lrow][t-1] == BLACK)&&(img[Lrow][t] == WHITE))
        {
            return(t-1);
        }
    }
    return(0);
}
//-----扫描左边沿，两个方向-----//
uint8 getL(uint8 Lrow,uint8 Lline,uint8 np)
{
    uint8 Lstart = 0,Lend = 0;//Lstart>Lend
    //限制Lline的值在0-79之间
    //限制Lrow的值在0-59之间
    if(Lline>LINE+50) Lline = 0;//防止Lline在自减过程中由0变为255,50是随便给的
    if(Lline>LINE&&Lline<=LINE+50) Lline = LINE;//防止Lline在自加过程中超过Line
    if(Lrow>ROW+50) Lrow = 0;
    if(Lrow>ROW&&Lrow<=ROW+50) Lrow = ROW;
    //限制Lstart的值在0-77之间
    //限制Lend的值在2-79之间
    if((Lline+np)>RBP)	Lstart=RBP;
    else	Lstart=Lline+np;
    if((Lline)<(LBP+np))	Lend=LBP;
    else	Lend=Lline-np;
    //限制Lline的值在2-77之间
    if(Lline>RBP)	Lline = RBP;
    if(Lline<LBP)	Lline = LBP;
    //限制t的值在0-77之间
    for(uint8 t=Lline-2; t<=Lstart; t++) //扫描方式||--->
    {
        if((img[Lrow][t] == BLACK)&&(img[Lrow][t+1] == BLACK)&&(img[Lrow][t+2] == WHITE))
        {
            return(t+1);//最大值78
        }
    }
    //限制t的值在2-79之间
    for(uint8 t=Lline+2; t>=Lend; t--) //扫描方式<---||
    {
        if((img[Lrow][t-2] == BLACK)&&(img[Lrow][t-1] == BLACK)&&(img[Lrow][t] == WHITE))
        {
            return(t-1);//最小值1
        }
    }
    return(0);
}
//-----扫描右边沿，一个方向-----//
uint8 getRs(uint8 Rrow,uint8 Rline,uint8 np)
{
    uint8 Rstart = 0,Rend = 0;// Rstart<Rend
    //限制Rline的值在0-79之间
    //限制Rrow的值在0-59之间
    if(Rline>LINE+50) Rline = 0;
    if(Rline>LINE&&Rline<=LINE+50) Rline = LINE;
    if(Rrow>ROW+50) Rrow = 0;
    if(Rrow>ROW&&Rrow<=ROW+50) Rrow = ROW;
    //限制Rstart的值在2-79之间
    //限制Rend的值在0-77之间
    if((LBP+np)>Rline)	Rstart = LBP;
    else	Rstart=Rline-np;
    if((Rline+np)>RBP)	Rend = RBP;
    else	Rend=Rline+np;
    //限制Rline的值在2-77之间
    if(Rline>RBP)	Rline = RBP;
    if(Rline<LBP)	Rline = LBP;
    //限制t的值在0-77之间
    for(uint8 t=Rstart-2; t<=Rend; t++) //扫描方式--->||--->
    {
        if((img[Rrow][t+2] == BLACK)&&(img[Rrow][t+1] == BLACK)&&(img[Rrow][t] == WHITE))
        {
            return(t+1);
        }
    }
    return(LINE);
}
//-----扫描右边沿，两个方向-----//
uint8 getR(uint8 Rrow,uint8 Rline,uint8 np)
{
    uint8 Rstart = 0,Rend = 0;// Rstart<Rend
    //限制Rline的值在0-79之间
    //限制Rrow的值在0-59之间
    if(Rline>LINE+50) Rline = 0;
    if(Rline>LINE&&Rline<=LINE+50) Rline = LINE;
    if(Rrow>ROW+50) Rrow = 0;
    if(Rrow>ROW&&Rrow<=ROW+50) Rrow = ROW;
    //限制Rstart的值在2-79之间
    //限制Rend的值在0-77之间
    if((LBP+np)>Rline)	Rstart = LBP;
    else	Rstart=Rline-np;
    if((Rline+np)>RBP)	Rend = RBP;
    else	Rend=Rline+np;
    //限制Rline的值在2-77之间
    if(Rline>RBP)	Rline = RBP;
    if(Rline<LBP)	Rline = LBP;
    //限制t的值在2-79之间
    for(uint8 t=Rline+2; t>=Rstart; t--) //扫描方式<---||
    {
        if((img[Rrow][t] == BLACK)&&(img[Rrow][t-1] == BLACK)&&(img[Rrow][t-2] == WHITE))
        {
            return(t-1);//最小值1
        }
    }
    //限制t的值在0-77之间
    for(uint8 t=Rline-2; t<=Rend; t++) //扫描方式||--->
    {
        if((img[Rrow][t+2] == BLACK)&&(img[Rrow][t+1] == BLACK)&&(img[Rrow][t] == WHITE))
        {
            return(t+1);//最大值78
        }
    }
    return(LINE);
}


//-----在找到左侧起跑线的时候，进行寻线-----//
void Handle_Left_Line()
{
    for(; l>END; l--)
    {
        Left[l-1]=getL(l-1,Left[l],8);
        if(Left[l-1]==0)	break;
    }
}
//-----在找到右侧起跑线的时候，进行寻线-----//
void Handle_Right_Line()
{
    for(; r>END; r--)
    {
        Right[r-1]=getR(r-1,Right[r],8);
        if(Right[r-1]==LINE)	break;
    }
}
//-----在没有找到左侧起跑线的时候，进行寻线-----//
void Find_Left_Line()
{
    //---处理左边界
    uint8 tem;
    uint8 temp,temp1;
    for(; l>END; l--)
    {
        temp = getL(l-1,0,5);//扫描靠近右边线的5个点	temp的值为73-79
        temp1 = getL(l-2,temp,5);

        if(temp != 0 && temp1 != 0)//搜到左边线
            break;
    }
    if(l <= 15) l = ROW;//没有搜到左边线
    else
    {
        tem = l;
        l--;
        Left[l] = temp;
        Handle_Left_Line();
        if(tem-l < 8)
            l = ROW;
    }
}
//-----在没有找到右侧起跑线的时候，进行寻线-----//
void Find_Right_Line()
{
    //----处理右边界
    uint8 tem;
    uint8 temp,temp1;
    for(; r>END; r--)
    {
        temp = getR(r-1,LINE,5);//扫描靠近右边线的5个点	temp的值为73-79
        temp1 = getR(r-2,temp,5);

        if(temp != LINE && temp1 != LINE)//搜到右边线
            break;
    }
    if(r <= 15) r = ROW;//没有搜到右边线
    else
    {
        tem = r;
        r--;
        Right[r] = temp;
        Handle_Right_Line();
        if(tem-r < 8)
            r = ROW;
    }
}
