#ifndef _hardware_H
#define _hardware_H
#include "common.h"
#include "include.h"

//�ṹ������
typedef struct
{
  float Angle,Angle_last;
  uint8 Angle_flg;
  float Kp,Kd;
  float P,D;//ʹ�ð���΢��
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


//��������
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

//��������
void OLED_ctrl();
void uart_ctrl();
void uart_wave();
void key_ctrl();
void parameter_init();
void OLED();



void protect_detect();//����Ƿ������
void protect(); //��������
void double_car_judge(); //�ж���������


#endif