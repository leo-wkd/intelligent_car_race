#include "overtake_round.h"
void overtake_speed()  //�����ٶȿ���
{










}
uint8 put_flg = 0;
uint8 tell_flg = 0;
uint8 enable_round_flg = 0;
uint32 find_round_num = 0 ;
void overtake_communication()//����ͨ��
{
    if(erwa_go) //˫��ģʽ
    {
        if(Car_State ==QIAN &&round_flg ==1&&put_flg==0) //ǰ�����ֻ������ߺ� �����������
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
    if(Round_Overtake_Enable) //����������
    {
        if(Car_State ==QIAN &&round_flg ==1&&tell_flg==0) //ǰ�����ֻ������ߺ� �����������
        {
            uart_putchar(UART2,2);
            uart_putchar(UART2,2);
            uart_putchar(UART2,2);
            tell_flg =1;
        }


    }
    else if(Car_State==HOU) //���������߼�
    {
        if(uart_get==1)
        {
            enable_round_flg = 1;
        }
        if(enable_round_flg ==1)
        {
            find_round_num ++;

        }
        if(find_round_num > 400)  // 400/75 = 6s ����
        {
            enable_round_flg = 0 ;
            uart_get = 0;
        }
    }






}
void overtake_straight()  //ֱ������
{









}
void overtake_round()  //��������

{






}
