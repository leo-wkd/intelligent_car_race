#include "overtake_round.h"
void overtake_speed()  //超车速度控制
{










}
uint8 put_flg = 0;
uint8 tell_flg = 0;
uint8 enable_round_flg = 0;
uint32 find_round_num = 0 ;
void overtake_communication()//超车通信
{
    if(erwa_go) //双车模式
    {
        if(Car_State ==QIAN &&round_flg ==1&&put_flg==0) //前车发现环岛告诉后车 开启环岛检测
        {
            uart_putchar(UART2,1);
            uart_putchar(UART2,1);
            uart_putchar(UART2,1);
            put_flg = 1;
        }
    }
    if(round_flg == 0 )
    {
        put_flg=0;
    }
    if(Round_Overtake_Enable) //环岛超车打开
    {
        if(Car_State ==QIAN &&round_flg ==1&&tell_flg==0) //前车发现环岛告诉后车 开启环岛检测
        {
            uart_putchar(UART2,2);
            uart_putchar(UART2,2);
            uart_putchar(UART2,2);
            tell_flg =1;
        }


    }
    else if(Car_State==HOU) //不超车后车逻辑
    {
        if(uart_get==1)
        {
            enable_round_flg = 1;
        }
        if(enable_round_flg ==1)
        {
            find_round_num ++;

        }
        if(find_round_num > 400)  // 400/75 = 6s 左右
        {
            enable_round_flg = 0 ;
            uart_get = 0;
        }
    }






}
void overtake_straight()  //直道超车
{









}
void overtake_round()  //环岛超车

{






}
