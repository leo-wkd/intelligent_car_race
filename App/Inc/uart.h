//#ifndef _uart_H
//#define _uart_H
//#include "include.h"
//
//
////���²�Ҫ�޸�
//#define UartRxBufferLen  100
//#define UartRxDataLen    41           //FreeCars��λ�����͸�������MCU���գ���Ҫ��
//#define UartRxCmdLen     7	      //FreeCars��λ�������������ݳ��ȣ���Ҫ��
//
//#define UartDataNum      17           //FreeCars��λ������ͨ������������λ�����øı�!!!
//
//#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//�����
//#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//��������
//
////��������
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
////��������
//void UART3_receive(void);
//void sendDataToScope(void);
//void push(uint8 adr,uint16 date);
//void sendCamImgToCamViewer(void);
//
//void produceCamRoadData(uint8);                  //ģ���������ͷͼ�����������������
//void sendRoadDataToCamViewer(uint8* LineData); //�����������ݵ���λ��
//
//void UartDebug(void);
//void UartCmd(uint8 CmdNum,uint8 Data);
//
//
//#endif