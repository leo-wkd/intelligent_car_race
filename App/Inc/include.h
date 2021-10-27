#ifndef __INCLUDE_H__
#define __INCLUDE_H__


//��
#define erwa_go 1	//1���󳵸��� 0������������
#define Straight_Overtake_Enable 0	//�Ƿ�ʹ��ֱ������
#define Cross_Overtake_Enable 0 //�Ƿ�ʹ��ʮ�ֳ���
#define Get_Start_Line get_start_line	//1:��������� 0�������������
#define Double_Car_Mode 1
#define Round_Overtake_Enable round_overtake_enable
#define Start_Line_Overtake start_line_overtake_enable

//����״̬
#define QIAN 'Q'

#define HOU  'H'
//LED����

#define ON 1
#define OFF 0



#include  "common.h"

/*
 * Include �û��Զ����ͷ�ļ�
 */
#include  "MK60_wdog.h"
#include  "MK60_gpio.h"     //IO�ڲ���
#include  "MK60_uart.h"     //����
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //�͹��Ķ�ʱ��(��ʱ)
#include  "MK60_pit.h"      //PIT
#include  "MK60_FLASH.h"    //FLASH
#include  "MK60_FTM.h"
#include  "MK60_adc.h"


//----------APP
#include "hardware.h"
#include "user_define.h"

//----------Drive
#include "Drive.h"
#include "Isr.h"
//---------GetLine
#include "GetLine.h"
//--------Control
#include "Control.h"
#include "overtake_straight.h"
#include "communication.h"
extern uint8 run_flg;



#endif  //__INCLUDE_H__
