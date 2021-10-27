#ifndef Control_H
#define Control_H
#include "common.h"
#include "include.h"



//函数声明
void Cacl_Error();
void Speed_Get();
void Speed_Set();
void Speed_Ctrl();
void Diff_Speed();
void Rudder_ctrl();
//变量声明
extern float error,error_pre[4],derror;
extern float Xielv;
extern int16 pulse_L,pulse_R;
extern float differ_2[];
extern float differ_1[];
extern float Xielv;
extern uint16 Uderror;
extern int16 speed_ave;
extern float curv;
extern int32  Slope_distance;
extern int16  Hightargetspeed[6];
extern uint8 moren_turn;
extern int8  overtakedir[10];
extern uint8 chao_checishu ;
extern uint8 chao_chedir;
#endif