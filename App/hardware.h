#ifndef _hardware_H
#define _hardware_H
#include "common.h"
#include "include.h"

//结构体声明
typedef struct
{
  float Angle,Angle_last;
  uint8 Angle_flg;
  float Kp,Kd;
  float P,D;//使用按键微调
}Rudder;
extern Rudder rudder;

typedef struct
{
  float targetspeed;
  float speed_error,speed_derror,speed_error_last,speed_dderror;
  float Kp,Kd,Kdd;
  float PWM_out;
  int16 pulse,pulse_last;
}Motor;
extern Motor motorL,motorR;

typedef struct
{
  uint8 trend;
  int8 error;
  int8 error_last;
  float targetspeed;
}Car;
extern Car car;


//变量声明
extern uint16 DJ_MAX;	
extern uint16 DJ_MID;	
extern uint16 DJ_MIN;	
extern uint8 protect_flg;
extern uint8 double_car_flg;
extern uint8 camLineData[120];
extern char Car_State;
extern uint8 round_overtake_enable;
extern uint8 get_start_line;
extern uint8 Slope_Threshold;
extern uint8 start_line_overtake_enable;

//函数声明
void OLED_ctrl();
void uart_ctrl();
void uart_wave();
void key_ctrl();
void parameter_init();
void OLED();



void protect_detect();//检测是否出赛道
void protect(); //保护程序
void double_car_judge(); //判断是哪辆车


#endif