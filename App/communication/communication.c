#include  "Drive.h"
#include "communication.h"

#define RC_MsgMAX_LEN   10
#define MAX_DATALEN     0x04
void put(uint8 ch)
{
   if(double_car_flg==1)
   {
     uart_putchar(UART0,ch);
   }
   else 
   {
     uart_putchar(UART3,ch);
   }

}

void car_send(uint8_t datatype,void * data)
{
    uint8_t type_len;
    uint8_t * dataptr = (uint8_t *)data;
    uint16_t check_sum=0;
    put(0x55);
    switch (datatype)
    {
    case TYPE_SPEED:
        type_len = TYPE_SPEED|LEN_SPEED;
        check_sum += type_len;
//        uart_putchar(UART0,type_len);
        put(type_len);
        for(type_len = 0; type_len<LEN_SPEED; type_len++)
        {
            check_sum += *dataptr;
            put(*dataptr++);
           // uart_putchar(UART0,*dataptr++);
        }
        check_sum = check_sum%255;
        put((uint8_t)check_sum);
        //uart_putchar(UART0,(uint8_t)check_sum);
        break;
    case TYPE_FLAG:
        type_len = TYPE_FLAG|LEN_FLAG;
        check_sum += type_len;
        put(type_len);
      //uart_putchar(UART0,type_len);
        for(type_len = 0; type_len<LEN_FLAG; type_len++)
        {
            check_sum += *dataptr;
             put(*dataptr++);
            //uart_putchar(UART0,*dataptr++);
        }
        check_sum = check_sum%255;
        put((uint8_t)check_sum);
        //uart_putchar(UART0,(uint8_t)check_sum);
        break;
    default:
        break;
    }
}




uint16  qian_speed;
uint8 flag;
int32 get_num;
void dataHander(uint8_t * data)
{
    uint8_t datatype;
    datatype = (*data)&0xF0;
    data++;
    switch (datatype)
    {
    case TYPE_SPEED:
        qian_speed = *((uint16_t *)data);
        break;
    case TYPE_FLAG:
        flag = *((uint8_t *)data);
        break;
    default:
        break;
    }
}

enum recstate //状态机
{
    RECFF1,RECLEN1,RECSEL,RECCHECK
} RC_Recstate = RECFF1;


void UartMsg_Hander(uint8_t data)
{
    static uint16_t checksum;
    static uint16_t RCdata_len;
    static uint32_t RCcur=0;
    static uint8_t RCbuffer[RC_MsgMAX_LEN];

    switch (RC_Recstate)
    {
    case RECFF1:
        if (data == 0x55)
        {
            RC_Recstate = RECLEN1;
            RCdata_len = 0;
            RCcur = 0;
            checksum=0;
        }
        break;

    case RECLEN1:
        if((data & 0x0F) <= MAX_DATALEN)
        {
            RCbuffer[RCcur++] = data;			//暂存数据
            RCdata_len = (data & 0x0F);
            checksum+=data;
            RC_Recstate = RECSEL;

        }
        else
        {
            RC_Recstate = RECFF1;
        }
        break;


    case RECSEL:
        RCbuffer[RCcur++] = data;			//暂存数据
        checksum+=data;
        if(RCcur >= RCdata_len+1)
        {
            RC_Recstate = RECCHECK;
        }
        break;

    case RECCHECK:
        checksum=checksum%255;
        if(checksum == data)
        {
            dataHander(RCbuffer);
            checksum=0;
            RC_Recstate = RECFF1;
           
        }
        else
        {
            RC_Recstate = RECFF1;
        }
        break;

    default:
        RC_Recstate = RECFF1;
        break;
    }

}



