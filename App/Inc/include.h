#ifndef __INCLUDE_H__
#define __INCLUDE_H__


//宏
#define erwa_go 1	//1：后车跟踪 0：后车自主运行
#define Straight_Overtake_Enable 0	//是否使能直道超车
#define Cross_Overtake_Enable 0 //是否使能十字超车
#define Get_Start_Line get_start_line	//1:检测起跑线 0：不检测起跑线
#define Double_Car_Mode 1
#define Round_Overtake_Enable round_overtake_enable
#define Start_Line_Overtake start_line_overtake_enable

//车的状态
#define QIAN 'Q'

#define HOU  'H'
//LED亮灭

#define ON 1
#define OFF 0



#include  "common.h"

/*
 * Include 用户自定义的头文件
 */
#include  "MK60_wdog.h"
#include  "MK60_gpio.h"     //IO口操作
#include  "MK60_uart.h"     //串口
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //低功耗定时器(延时)
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
