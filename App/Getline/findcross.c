#include "getline.h"

//-----��ȡʮ��-----//
uint8 cross_flg = 0;
uint8 shizi_flg = 0;
void Find_Cross()
{
    uint8 L = 0,R = 0;
    cross_flg = 0;
    //��������
    for(L = ROW-2; L>=l+2; L--)
    {
        //�ҹյ�
        if(Left[L]>Left[L+2] && Left[L]>Left[L-2])
        {
            //������б��
            float xielv = 0;
            float xielv_1 = 0;
            float xielv_2 = 0;

            uint8 i = L -1;
            uint8 j = L;
            for(; j>l; j--)
                if(Left[j] < Left[j+1]) break;

            i = j;
            for(; i>l; i--)
            {
                if(Left[j+1] - Left[i]>=0)
                    xielv_1 += (float)(Left[j+1] - Left[i])/(j+1 - i);
                else break;
            }

            if(xielv_1 != 0)
            {
                xielv_1 /= (j-i);
                xielv_1 = 1/xielv_1;
            }

            //������б��
            j = L;
            for(; j>l; j--)
                if(Left[j] <= Left[j+1]) break;

            i = j+2;
            for(; i<=ROW; i++)
            {
                if(Left[j+1] - Left[i] >=0)
                    xielv_2 += (float)(Left[j+1] - Left[i])/(i - j-1);
                else break;
            }

            if(xielv_2 != 0)
            {
                xielv_2 /= (i-2-j);
                xielv_2 = 1/xielv_2;
            }

            //�жϼн�
            xielv = xielv_1*xielv_2;
            if(xielv<1 && xielv!=0) //�����
            {
                if(L>15)//���Ƽ�����
                {
                    cross_flg |= 0xf0;
                }
            }
            break;
        }
    }
    //����ұ���
    for(R = ROW-2; R>=r+2; R--)
    {
        //�ҹյ�
        if(Right[R]<Right[R+2] && Right[R]<Right[R-2])
        {
            //������б��
            float xielv = 0;
            float xielv_1 = 0;
            float xielv_2 = 0;
            uint8 i = R -1;
            uint8 j = R;

            for(; j>r; j--)
                if(Right[j] > Right[j+1]) break;

            i = j;
            for(; i>r; i--)
            {
                if(Right[i] - Right[j+1]>=0)
                    xielv_1 += (float)(Right[i] - Right[j+1])/(j+1 - i);
                else break;
            }

            if(xielv_1 != 0)
            {
                xielv_1 /= (j-i);
                xielv_1 = 1/xielv_1;
            }

            //������б��
            j = R;
            for(; j>r; j--)
                if(Right[j] >= Right[j+1]) break;

            i = j+2;
            for(; i<=ROW; i++)
            {
                if(Right[i] - Right[j+1]>=0)
                    xielv_2 += (float)(Right[i] - Right[j+1])/(i - j-1);
                else break;
            }

            if(xielv_2 != 0)
            {
                xielv_2 /= (i-j-2);
                xielv_2 = 1/xielv_2;
            }
            //�жϼн�
            xielv = xielv_1*xielv_2;
            if(xielv<1 && xielv!=0) //�����
            {
                if(R>15)//���Ƽ�����
                {
                    cross_flg |= 0x0f;
                }
            }
            break;
        }
    }
        if(cross_flg!=0x00)
        {
        shizi_flg = 1;

        }
        else
        {
        shizi_flg = 0;
        }
    //-----����-----//
    if((cross_flg&0xf0) == 0xf0)//��⵽�����
    {
        //����

        uint8 i = L;
        for(; i>10; i--)
        {
            if(Right[i]<=Left[i]) break;
            Left[i - 1] = Left[i] + 1;
        }
        l = i+1>ROW?ROW:i+1;

    }

    if((cross_flg&0x0f) == 0x0f)//��⵽�ұ���
    {
        //����

        uint8 i = R;
        for(; i>10; i--)
        {
            if(Right[i]<=Left[i]) break;
            Right[i - 1] = Right[i] - 1;
        }
        r = i+1>ROW?ROW:i+1;
    }

}
//------ʮ����ش���-----//
void Fix_Blank()
{
    //-----��߿հײ���-----//
    if(l>55)
    {
        //---��������ʼ���ֵĺڵ�
        uint8 start = ROW;
        if(img[ROW][0] == BLACK)
            for(uint8 k=ROW; k>0; k--)
            {
                if(k < l-2)	goto here;//��һ�кڵ������࣬�Ƴ�
                if(img[k][0] == WHITE)
                {
                    start = k;
                    break;
                }
            }
        uint8 end = ROW;
        for(uint8 k=start; k>20; k--) //����һ�а׵��յ�
        {
            if(img[k][0] == BLACK)
            {
                break;
            }
            else
            {
                end = k;
            }
        }

        if(start-end>=5)
        {
            uint8 L_temp_1 = 0;
            uint8 L_temp_2 = 0;

            //���������
            uint8 i=start;
            for(; i>end-3; i--)
            {
                L_temp_1 = getL(i,10,20);
                L_temp_2 = getL(i-1,L_temp_1,7);
                if((L_temp_1!=0)&&(L_temp_2!=0))
                    break;
            }
            if(L_temp_1>4)
            {
                //���²���
                uint8 x0 = 0;
                uint8 y0 = ROW;
                uint8 x1 = L_temp_1;
                uint8 y1 = i;
                for(uint8 k = i; k < ROW; k++)
                {
                    Left[k]=x0+(y0-k)*(x1-x0)/(y0-y1);
                }
                //����Ѱ��
                Left[i] = L_temp_1;
                l = i;
                Handle_Left_Line();
            }
        }
    }

    //-----�ұ߿հײ���-----//
here:
    if(r>55)
    {
        //---��������ʼ���ֵĺڵ�
        uint8 start = ROW;
        if(img[ROW][LINE] == BLACK)
            for(uint8 k=ROW; k>0; k--)
            {
                if(k < r-2)	return;
                if(img[k][LINE] == WHITE)
                {
                    start = k;
                    break;
                }
            }
        uint8 end = ROW;
        for(uint8 k=start; k>20; k--) //����һ�а׵��յ�
        {
            if(img[k][LINE] == BLACK)
            {
                break;
            }
            else
            {
                end = k;
            }
        }

        if(start-end>=5)
        {
            uint8 R_temp_1 = LINE;
            uint8 R_temp_2 = LINE;
            //�����ұ���
            uint8 i=start;
            for(; i>end-3; i--)
            {
                R_temp_1 = getR(i,70,20);
                R_temp_2 = getR(i-1,R_temp_1,7);
                if((R_temp_1!=LINE)&&(R_temp_2!=LINE))
                    break;
            }
            if(R_temp_1<=75)
            {
                //���²���
                uint8 x0 = LINE;
                uint8 y0 = ROW;
                uint8 x1 = R_temp_1;
                uint8 y1 = i;
                for(uint8 k = i; k < ROW; k++)
                {
                    Right[k]=x0-(y0-k)*(x0-x1)/(y0-y1);
                }
                //����Ѱ��
                Right[i] = R_temp_1;
                r = i;
                Handle_Right_Line();
            }
        }
    }
}
