//鹰眼ov7725驱动代码

#ifndef Eagle_H_
#define Eagle_H_

#include "OV7725_REG.h"
#include "Sccb.h"


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



#endif


