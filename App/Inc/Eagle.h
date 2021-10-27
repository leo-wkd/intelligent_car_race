//ӥ��ov7725��������

#ifndef Eagle_H_
#define Eagle_H_

#include "OV7725_REG.h"
#include "Sccb.h"


typedef struct
{
    uint8 addr;                 /*�Ĵ�����ַ*/
    uint8 val;                   /*�Ĵ���ֵ*/
} reg_s;



//��������ͷ����ӿ�
#define camera_init(imgaddr)    ov7725_eagle_init(imgaddr)

#define camera_vsync()          ov7725_eagle_vsync()
#define camera_dma()            ov7725_eagle_dma()



//��������ͷ ����
#define OV7725_EAGLE_DMA_CH       DMA_CH0                               //��������ͷ��DMA�ɼ�ͨ��
#define OV7725_EAGLE_W            80                                    //��������ͷͼ����
#define OV7725_EAGLE_H            60                                    //��������ͷͼ��߶�
#define OV7725_EAGLE_SIZE         (OV7725_EAGLE_W * OV7725_EAGLE_H/8 )  //ͼ��ռ�ÿռ��С
#define OV7725_EAGLE_DMA_NUM      (OV7725_EAGLE_SIZE )                  //DMA�ɼ�����

//���� ����ͷ ����
#define CAMERA_DMA_CH       OV7725_EAGLE_DMA_CH         //��������ͷ��DMA�ɼ�ͨ��
#define CAMERA_W            OV7725_EAGLE_W              //��������ͷͼ����
#define CAMERA_H            OV7725_EAGLE_H              //��������ͷͼ��߶�

#define CAMERA_SIZE         OV7725_EAGLE_SIZE           //ͼ��ռ�ÿռ��С
#define CAMERA_DMA_NUM      OV7725_EAGLE_DMA_NUM        //DMA�ɼ�����

extern uint8 Pic_complete;
extern uint8 imgbuff[CAMERA_SIZE]; //����洢����ͼ�������
extern uint8 img[CAMERA_H][CAMERA_W];

uint8 ov7725_eagle_init(uint8 *imgaddr);
void ov7725_eagle_get_img(void);

void ov7725_eagle_vsync(void);
void ov7725_eagle_dma(void);
void img_extract(uint8 *dst, uint8 *src, uint32 srclen);



#endif


