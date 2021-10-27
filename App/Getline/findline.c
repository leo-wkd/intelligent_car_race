#include "getline.h"


//-----ɨ������أ�һ������-----//
uint8 getLs(uint8 Lrow,uint8 Lline,uint8 np)
{
    uint8 Lstart = 0,Lend = 0;//Lstart>Lend
    //����Lline��ֵ��0-79֮��
    //����Lrow��ֵ��0-59֮��
    if(Lline>LINE+50) Lline = 0;
    if(Lline>LINE&&Lline<=LINE+50) Lline = LINE;
    if(Lrow>ROW+50) Lrow = 0;
    if(Lrow>ROW&&Lrow<=ROW+50) Lrow = ROW;
    //����Lstart��ֵ��0-77֮��
    //����Lend��ֵ��2-79֮��
    if((Lline+np)>RBP)	Lstart=RBP;
    else	Lstart=Lline+np;
    if((Lline)<(LBP+np))	Lend=LBP;
    else	Lend=Lline-np;
    //����Lline��ֵ��2-77֮��
    if(Lline>RBP)	Lline = RBP;
    if(Lline<LBP)	Lline = LBP;
    //����t��ֵ��2-79֮��
    for(uint8 t=Lstart+2; t>=Lend; t--) //ɨ�跽ʽ<---||<---
    {
        if((img[Lrow][t-2] == BLACK)&&(img[Lrow][t-1] == BLACK)&&(img[Lrow][t] == WHITE))
        {
            return(t-1);
        }
    }
    return(0);
}
//-----ɨ������أ���������-----//
uint8 getL(uint8 Lrow,uint8 Lline,uint8 np)
{
    uint8 Lstart = 0,Lend = 0;//Lstart>Lend
    //����Lline��ֵ��0-79֮��
    //����Lrow��ֵ��0-59֮��
    if(Lline>LINE+50) Lline = 0;//��ֹLline���Լ���������0��Ϊ255,50��������
    if(Lline>LINE&&Lline<=LINE+50) Lline = LINE;//��ֹLline���Լӹ����г���Line
    if(Lrow>ROW+50) Lrow = 0;
    if(Lrow>ROW&&Lrow<=ROW+50) Lrow = ROW;
    //����Lstart��ֵ��0-77֮��
    //����Lend��ֵ��2-79֮��
    if((Lline+np)>RBP)	Lstart=RBP;
    else	Lstart=Lline+np;
    if((Lline)<(LBP+np))	Lend=LBP;
    else	Lend=Lline-np;
    //����Lline��ֵ��2-77֮��
    if(Lline>RBP)	Lline = RBP;
    if(Lline<LBP)	Lline = LBP;
    //����t��ֵ��0-77֮��
    for(uint8 t=Lline-2; t<=Lstart; t++) //ɨ�跽ʽ||--->
    {
        if((img[Lrow][t] == BLACK)&&(img[Lrow][t+1] == BLACK)&&(img[Lrow][t+2] == WHITE))
        {
            return(t+1);//���ֵ78
        }
    }
    //����t��ֵ��2-79֮��
    for(uint8 t=Lline+2; t>=Lend; t--) //ɨ�跽ʽ<---||
    {
        if((img[Lrow][t-2] == BLACK)&&(img[Lrow][t-1] == BLACK)&&(img[Lrow][t] == WHITE))
        {
            return(t-1);//��Сֵ1
        }
    }
    return(0);
}
//-----ɨ���ұ��أ�һ������-----//
uint8 getRs(uint8 Rrow,uint8 Rline,uint8 np)
{
    uint8 Rstart = 0,Rend = 0;// Rstart<Rend
    //����Rline��ֵ��0-79֮��
    //����Rrow��ֵ��0-59֮��
    if(Rline>LINE+50) Rline = 0;
    if(Rline>LINE&&Rline<=LINE+50) Rline = LINE;
    if(Rrow>ROW+50) Rrow = 0;
    if(Rrow>ROW&&Rrow<=ROW+50) Rrow = ROW;
    //����Rstart��ֵ��2-79֮��
    //����Rend��ֵ��0-77֮��
    if((LBP+np)>Rline)	Rstart = LBP;
    else	Rstart=Rline-np;
    if((Rline+np)>RBP)	Rend = RBP;
    else	Rend=Rline+np;
    //����Rline��ֵ��2-77֮��
    if(Rline>RBP)	Rline = RBP;
    if(Rline<LBP)	Rline = LBP;
    //����t��ֵ��0-77֮��
    for(uint8 t=Rstart-2; t<=Rend; t++) //ɨ�跽ʽ--->||--->
    {
        if((img[Rrow][t+2] == BLACK)&&(img[Rrow][t+1] == BLACK)&&(img[Rrow][t] == WHITE))
        {
            return(t+1);
        }
    }
    return(LINE);
}
//-----ɨ���ұ��أ���������-----//
uint8 getR(uint8 Rrow,uint8 Rline,uint8 np)
{
    uint8 Rstart = 0,Rend = 0;// Rstart<Rend
    //����Rline��ֵ��0-79֮��
    //����Rrow��ֵ��0-59֮��
    if(Rline>LINE+50) Rline = 0;
    if(Rline>LINE&&Rline<=LINE+50) Rline = LINE;
    if(Rrow>ROW+50) Rrow = 0;
    if(Rrow>ROW&&Rrow<=ROW+50) Rrow = ROW;
    //����Rstart��ֵ��2-79֮��
    //����Rend��ֵ��0-77֮��
    if((LBP+np)>Rline)	Rstart = LBP;
    else	Rstart=Rline-np;
    if((Rline+np)>RBP)	Rend = RBP;
    else	Rend=Rline+np;
    //����Rline��ֵ��2-77֮��
    if(Rline>RBP)	Rline = RBP;
    if(Rline<LBP)	Rline = LBP;
    //����t��ֵ��2-79֮��
    for(uint8 t=Rline+2; t>=Rstart; t--) //ɨ�跽ʽ<---||
    {
        if((img[Rrow][t] == BLACK)&&(img[Rrow][t-1] == BLACK)&&(img[Rrow][t-2] == WHITE))
        {
            return(t-1);//��Сֵ1
        }
    }
    //����t��ֵ��0-77֮��
    for(uint8 t=Rline-2; t<=Rend; t++) //ɨ�跽ʽ||--->
    {
        if((img[Rrow][t+2] == BLACK)&&(img[Rrow][t+1] == BLACK)&&(img[Rrow][t] == WHITE))
        {
            return(t+1);//���ֵ78
        }
    }
    return(LINE);
}


//-----���ҵ���������ߵ�ʱ�򣬽���Ѱ��-----//
void Handle_Left_Line()
{
    for(; l>END; l--)
    {
        Left[l-1]=getL(l-1,Left[l],8);
        if(Left[l-1]==0)	break;
    }
}
//-----���ҵ��Ҳ������ߵ�ʱ�򣬽���Ѱ��-----//
void Handle_Right_Line()
{
    for(; r>END; r--)
    {
        Right[r-1]=getR(r-1,Right[r],8);
        if(Right[r-1]==LINE)	break;
    }
}
//-----��û���ҵ���������ߵ�ʱ�򣬽���Ѱ��-----//
void Find_Left_Line()
{
    //---������߽�
    uint8 tem;
    uint8 temp,temp1;
    for(; l>END; l--)
    {
        temp = getL(l-1,0,5);//ɨ�迿���ұ��ߵ�5����	temp��ֵΪ73-79
        temp1 = getL(l-2,temp,5);

        if(temp != 0 && temp1 != 0)//�ѵ������
            break;
    }
    if(l <= 15) l = ROW;//û���ѵ������
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
//-----��û���ҵ��Ҳ������ߵ�ʱ�򣬽���Ѱ��-----//
void Find_Right_Line()
{
    //----�����ұ߽�
    uint8 tem;
    uint8 temp,temp1;
    for(; r>END; r--)
    {
        temp = getR(r-1,LINE,5);//ɨ�迿���ұ��ߵ�5����	temp��ֵΪ73-79
        temp1 = getR(r-2,temp,5);

        if(temp != LINE && temp1 != LINE)//�ѵ��ұ���
            break;
    }
    if(r <= 15) r = ROW;//û���ѵ��ұ���
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
