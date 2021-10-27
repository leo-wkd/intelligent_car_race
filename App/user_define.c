#include "user_define.h"

//********************求绝对值
uint8 uabs8(int8 x)
{
    return x>0?x:-x;
}

uint16 uabs16(int16 x)
{
    return x>0?x:-x;
}

uint32 uabs32(int32 x)
{
    return x>0?x:-x;
}

float ufabs(float x)
{
    return x>0?x:-x;
}
//****************求两数差值
uint8 abt(uint8 a,uint8 b)
{
    return a>b?a-b:b-a;
}

uint32 abt32(uint32 a,uint32 b)
{
    return a>b?a-b:b-a;
}


float abtf(float a,float b)
{
    return a>b?a-b:b-a;
}
uint16 Sqrt(uint8 x)
{
    unsigned char ans = 0 ,p= 0x80;
    while(p!=0)
    {
        ans+=p;
        if(ans * ans >x )
        {
            ans -= p;
        }
        p=(unsigned char )(p/2);
    }

    return ans;
}
