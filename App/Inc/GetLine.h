#ifndef _getline_H
#define _getline_H
#include "include.h"

#define RBP 77  //右边开始点
#define LBP 2//左边开始点
#define MID 40//中点一行
#define END 5//摄像头提线时的最远处

#define ROW  59  //0-59共60行
#define LINE 79  //0-79共80列
#define WHITE 255
#define BLACK 0
//变量声明
extern int8 Mid[ROW+1];
extern int16 Left[ROW+1];
extern int16 Right[ROW+1];
extern uint8 Length1[ROW+1];
extern uint8 Length2[ROW+1];
extern uint8 r,l,m;
extern uint8 Slope_flg;
extern uint8 crossflg;
extern uint8 startflg;
extern uint8 flag;
extern uint8 LaststartpointL;//预设左边点
extern uint8 LaststartpointR;//预设右边点
extern float xielv_1;
extern float xielv_2 ;
extern uint8 cross_flg;
extern unsigned char round_flg;
extern uint8 roundspeed_flg;
extern uint8 round_continue;
extern uint8 big_flg;
extern uint8 Slope_flg ;
extern uint8 turn_flg;
extern uint8 GetLine_Error_flg;
extern uint8 round_rudder_flg;
extern uint8 out_flg;
extern uint8 stop_flg;
extern uint8 sstop_flg;
extern uint8 break_flg;
extern uint8 shizi_flg;
extern uint8 bround_start;
extern uint8 sround_start;
extern uint8 break_flg;
extern uint8 stop_flg;
extern uint8 start_finish_flg;
//函数声明
void GetLine();
void getline();
void getstart();
void getmiddleline();
void Find_Cross();
void Fix_Blank();
void findzhangai();;
void qipao_stop();
void stop();
uint8 getLs(uint8 Lrow,uint8 Lline,uint8 np);
uint8 getL(uint8 Lrow,uint8 Lline,uint8 np);
uint8 getRs(uint8 Rrow,uint8 Rline,uint8 np);
uint8 getR(uint8 Rrow,uint8 Rline,uint8 np);
extern void findround();
extern void get_startline();
void Handle_Left_Line();
void Handle_Right_Line();
void Find_Left_Line();
void Find_Right_Line();

#endif