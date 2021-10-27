#ifndef _Drive_H
#define _Drive_H
#include "common.h"
#include "include.h"

///*************************************SCCB模块************************************************************************//
//OV摄像头配置总线SCCB函数库
//SCCB 管脚配置
#define SCCB_SCL        PTB9
#define SCCB_SDA        PTB8


#define SCL_H()         PTXn_T(SCCB_SCL,OUT) = 1
#define SCL_L()         PTXn_T(SCCB_SCL,OUT) = 0
#define SCL_DDR_OUT()   PTXn_T(SCCB_SCL,DDR) = 1
#define SCL_DDR_IN()    PTXn_T(SCCB_SCL,DDR) = 0

#define SDA_H()         PTXn_T(SCCB_SDA,OUT) = 1
#define SDA_L()         PTXn_T(SCCB_SDA,OUT) = 0
#define SDA_IN()        PTXn_T(SCCB_SDA,IN)
#define SDA_DDR_OUT()   PTXn_T(SCCB_SDA,DDR) = 1
#define SDA_DDR_IN()    PTXn_T(SCCB_SDA,DDR) = 0

#define ADDR_OV7725   0x42
#define ADDR_OV7620   0x42

#define DEV_ADR  ADDR_OV7725             /*设备地址定义*/

#define SCCB_DELAY()    SCCB_delay(400)


extern void SCCB_GPIO_init(void);
extern int SCCB_WriteByte( uint16 WriteAddress , uint8 SendByte);
extern int SCCB_ReadByte(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress);
extern void Fm();



//****************************上位机模块************************************//
//以下不要修改
#define UartRxBufferLen  100
#define UartRxDataLen    41           //FreeCars上位机发送浮点数据MCU接收，不要改
#define UartRxCmdLen     7	      //FreeCars上位机接收命令数据长度，不要改

#define UartDataNum      17           //FreeCars上位机接收通道数，按照上位机设置改变!!!

#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//命令号
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//命令数据

//变量声明
typedef struct
{
  int32 Stack;
  uint8 Data;
  uint8 PreData;
  uint8 Buffer[UartRxBufferLen];
  uint8 Enable;
  uint8 Check;
}SerialPortType;

//函数声明
void UART3_receive(void);
void sendDataToScope(void);
void push(uint8 adr,uint16 date);
void sendCamImgToCamViewer(void);

void produceCamRoadData(uint8);                  //模拟产生摄像头图像处理出来的赛道数据
void sendRoadDataToCamViewer(uint8* LineData); //发送赛道数据到上位机

void UartDebug(void);
void UartCmd(uint8 CmdNum,uint8 Data);
//
//

//***********************************************鹰眼ov7725REG**********************************************************//
#define OV7725_ID        0x21
#define OV7725_GAIN      0x00
#define OV7725_BLUE      0x01
#define OV7725_RED       0x02
#define OV7725_GREEN     0x03
#define OV7725_BAVG      0x05
#define OV7725_GAVG      0x06
#define OV7725_RAVG      0x07
#define OV7725_AECH      0x08
#define OV7725_COM2      0x09
#define OV7725_PID       0x0A
#define OV7725_VER       0x0B
#define OV7725_COM3      0x0C
#define OV7725_COM4      0x0D
#define OV7725_COM5      0x0E
#define OV7725_COM6      0x0F
#define OV7725_AEC       0x10
#define OV7725_CLKRC     0x11
#define OV7725_COM7      0x12
#define OV7725_COM8      0x13
#define OV7725_COM9      0x14
#define OV7725_COM10     0x15
#define OV7725_REG16     0x16
#define OV7725_HSTART    0x17
#define OV7725_HSIZE     0x18
#define OV7725_VSTRT     0x19
#define OV7725_VSIZE     0x1A
#define OV7725_PSHFT     0x1B
#define OV7725_MIDH      0x1C
#define OV7725_MIDL      0x1D
#define OV7725_LAEC      0x1F
#define OV7725_COM11     0x20
#define OV7725_BDBase    0x22
#define OV7725_BDMStep   0x23
#define OV7725_AEW       0x24
#define OV7725_AEB       0x25
#define OV7725_VPT       0x26
#define OV7725_REG28     0x28
#define OV7725_HOutSize  0x29
#define OV7725_EXHCH     0x2A
#define OV7725_EXHCL     0x2B
#define OV7725_VOutSize  0x2C
#define OV7725_ADVFL     0x2D
#define OV7725_ADVFH     0x2E
#define OV7725_YAVE      0x2F
#define OV7725_LumHTh    0x30
#define OV7725_LumLTh    0x31
#define OV7725_HREF      0x32
#define OV7725_DM_LNL    0x33
#define OV7725_DM_LNH    0x34
#define OV7725_ADoff_B   0x35
#define OV7725_ADoff_R   0x36
#define OV7725_ADoff_Gb  0x37
#define OV7725_ADoff_Gr  0x38
#define OV7725_Off_B     0x39
#define OV7725_Off_R     0x3A
#define OV7725_Off_Gb    0x3B
#define OV7725_Off_Gr    0x3C
#define OV7725_COM12     0x3D
#define OV7725_COM13     0x3E
#define OV7725_COM14     0x3F
#define OV7725_COM16     0x41
#define OV7725_TGT_B     0x42
#define OV7725_TGT_R     0x43
#define OV7725_TGT_Gb    0x44
#define OV7725_TGT_Gr    0x45
#define OV7725_LC_CTR    0x46
#define OV7725_LC_XC     0x47
#define OV7725_LC_YC     0x48
#define OV7725_LC_COEF   0x49
#define OV7725_LC_RADI   0x4A
#define OV7725_LC_COEFB  0x4B
#define OV7725_LC_COEFR  0x4C
#define OV7725_FixGain   0x4D
#define OV7725_AREF1     0x4F
#define OV7725_AREF6     0x54
#define OV7725_UFix      0x60
#define OV7725_VFix      0x61
#define OV7725_AWBb_blk  0x62
#define OV7725_AWB_Ctrl0 0x63
#define OV7725_DSP_Ctrl1 0x64
#define OV7725_DSP_Ctrl2 0x65
#define OV7725_DSP_Ctrl3 0x66
#define OV7725_DSP_Ctrl4 0x67
#define OV7725_AWB_bias  0x68
#define OV7725_AWBCtrl1  0x69
#define OV7725_AWBCtrl2  0x6A
#define OV7725_AWBCtrl3  0x6B
#define OV7725_AWBCtrl4  0x6C
#define OV7725_AWBCtrl5  0x6D
#define OV7725_AWBCtrl6  0x6E
#define OV7725_AWBCtrl7  0x6F
#define OV7725_AWBCtrl8  0x70
#define OV7725_AWBCtrl9  0x71
#define OV7725_AWBCtrl10 0x72
#define OV7725_AWBCtrl11 0x73
#define OV7725_AWBCtrl12 0x74
#define OV7725_AWBCtrl13 0x75
#define OV7725_AWBCtrl14 0x76
#define OV7725_AWBCtrl15 0x77
#define OV7725_AWBCtrl16 0x78
#define OV7725_AWBCtrl17 0x79
#define OV7725_AWBCtrl18 0x7A
#define OV7725_AWBCtrl19 0x7B
#define OV7725_AWBCtrl20 0x7C
#define OV7725_AWBCtrl21 0x7D
#define OV7725_GAM1      0x7E
#define OV7725_GAM2      0x7F
#define OV7725_GAM3      0x80
#define OV7725_GAM4      0x81
#define OV7725_GAM5      0x82
#define OV7725_GAM6      0x83
#define OV7725_GAM7      0x84
#define OV7725_GAM8      0x85
#define OV7725_GAM9      0x86
#define OV7725_GAM10     0x87
#define OV7725_GAM11     0x88
#define OV7725_GAM12     0x89
#define OV7725_GAM13     0x8A
#define OV7725_GAM14     0x8B
#define OV7725_GAM15     0x8C
#define OV7725_SLOP      0x8D
#define OV7725_DNSTh     0x8E
#define OV7725_EDGE0     0x8F
#define OV7725_EDGE1     0x90
#define OV7725_DNSOff    0x91
#define OV7725_EDGE2     0x92
#define OV7725_EDGE3     0x93
#define OV7725_MTX1      0x94
#define OV7725_MTX2      0x95
#define OV7725_MTX3      0x96
#define OV7725_MTX4      0x97
#define OV7725_MTX5      0x98
#define OV7725_MTX6      0x99
#define OV7725_MTX_Ctrl  0x9A
#define OV7725_BRIGHT    0x9B
#define OV7725_CNST      0x9C
#define OV7725_UVADJ0    0x9E
#define OV7725_UVADJ1    0x9F
#define OV7725_SCAL0     0xA0
#define OV7725_SCAL1     0xA1
#define OV7725_SCAL2     0xA2
#define OV7725_SDE       0xA6
#define OV7725_USAT      0xA7
#define OV7725_VSAT      0xA8
#define OV7725_HUECOS    0xA9
#define OV7725_HUESIN    0xAA
#define OV7725_SIGN      0xAB
#define OV7725_DSPAuto   0xAC



//**********************************************鹰眼ov7725驱动代码******************************************************//
typedef struct
{
    uint8 addr;                 /*寄存器地址*/
    uint8 val;                   /*寄存器值*/
} reg_s;
//配置摄像头顶层接口
#define camera_init(imgaddr)    ov7725_eagle_init(imgaddr)

#define camera_vsync()          ov7725_eagle_vsync()
#define camera_dma()            ov7725_eagle_dma()
//配置摄像头 属性
#define OV7725_EAGLE_DMA_CH       DMA_CH0                               //定义摄像头的DMA采集通道
#define OV7725_EAGLE_W            80                                    //定义摄像头图像宽度
#define OV7725_EAGLE_H            60                                    //定义摄像头图像高度
#define OV7725_EAGLE_SIZE         (OV7725_EAGLE_W * OV7725_EAGLE_H/8 )  //图像占用空间大小
#define OV7725_EAGLE_DMA_NUM      (OV7725_EAGLE_SIZE )                  //DMA采集次数
//配置 摄像头 参数
#define CAMERA_DMA_CH       OV7725_EAGLE_DMA_CH         //定义摄像头的DMA采集通道
#define CAMERA_W            OV7725_EAGLE_W              //定义摄像头图像宽度
#define CAMERA_H            OV7725_EAGLE_H              //定义摄像头图像高度
#define CAMERA_SIZE         OV7725_EAGLE_SIZE           //图像占用空间大小
#define CAMERA_DMA_NUM      OV7725_EAGLE_DMA_NUM        //DMA采集次数
extern uint8 Pic_complete;
extern uint8 imgbuff[CAMERA_SIZE]; //定义存储接收图像的数组
extern uint8 img[CAMERA_H][CAMERA_W];
uint8 ov7725_eagle_init(uint8 *imgaddr);
void ov7725_eagle_get_img(void);
void ov7725_eagle_vsync(void);
void ov7725_eagle_dma(void);
void img_extract(uint8 *dst, uint8 *src, uint32 srclen);
//***********************************************硬件初始化***************************************************//
//变量声明
extern uint8 key_value;

//函数声明
void hardware_init();
void LED1(uint8 i);
void LED2(uint8 i);
void LED3(uint8 i);
void LED4(uint8 i);

void key(void);
void boma(void);
void num(uint8 num);
//******************OLED***********************************************************//
/*****************************设置数据类型*****************************/
typedef 	unsigned 	char		u8;	  //无符号型
typedef 	unsigned 	short int	u16;
typedef 	unsigned 	long  int	u32;

typedef 	char					s8;	  //有符号型
typedef 	short int				s16;
typedef 	long  int				s32;
/********************************************************************/
 void OLED_CLS(void);
 void OLED_Set_Pos(u8 x, u8 y);
 void OLED_WrDat(u8 data);
 void Draw_BMP(uint8 bmp[]);//显示BMP图片128×64
 void Dly_ms(u16 ms);
 void OLED_WrCmd(u8 cmd);

 void OLED_PutPixel(u8 x,u8 y);	//绘制一个点
 void OLED_Rectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 gif);	//绘制一个实心矩形


 //---------------要调用的函数
 void OLED_Init(void);		//必须
 void OLED_Fill(u8 dat);
 void Oled_Img(uint8 * img);
 void OLED_Print(u8 x, u8 y, u8 ch[]);//显示汉字
 void OLED_P6x8Str(u8 x,u8 y,u8 ch[]);	//显示字符串
 void OLED_6x8Char(u8 X1,u8 Y1,u8 Data1); //显示char
 void OLED_PrintValueI(uint8 x, uint8 y, int16 data);        		 //显示int
 void OLED_PrintValueF(uint8 x, uint8 y, float data, uint8 num); 	//显示float
                                                               		//num最大为4
 extern uint8 my_CAR[];
 extern uint8 my_PIG[];
 extern uint8 F14x16_Idx[];
 extern uint8 F14x16[];
 
#endif


