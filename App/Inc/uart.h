//#ifndef _uart_H
//#define _uart_H
//#include "include.h"
//
//
////以下不要修改
//#define UartRxBufferLen  100
//#define UartRxDataLen    41           //FreeCars上位机发送浮点数据MCU接收，不要改
//#define UartRxCmdLen     7	      //FreeCars上位机接收命令数据长度，不要改
//
//#define UartDataNum      17           //FreeCars上位机接收通道数，按照上位机设置改变!!!
//
//#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//命令号
//#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//命令数据
//
////变量声明
//typedef struct
//{
//  int32 Stack;
//  uint8 Data;
//  uint8 PreData;
//  uint8 Buffer[UartRxBufferLen];
//  uint8 Enable;
//  uint8 Check;
//}SerialPortType;
//
////函数声明
//void UART3_receive(void);
//void sendDataToScope(void);
//void push(uint8 adr,uint16 date);
//void sendCamImgToCamViewer(void);
//
//void produceCamRoadData(uint8);                  //模拟产生摄像头图像处理出来的赛道数据
//void sendRoadDataToCamViewer(uint8* LineData); //发送赛道数据到上位机
//
//void UartDebug(void);
//void UartCmd(uint8 CmdNum,uint8 Data);
//
//
//#endif