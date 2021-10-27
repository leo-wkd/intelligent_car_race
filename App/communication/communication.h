#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H	

#include "stdint.h"


#define TYPE_SPEED   0x10
#define TYPE_FLAG    0x20
#define LEN_SPEED    0x02
#define LEN_FLAG     0x01
extern uint16  qian_speed;
extern uint8 flag;

void car_send(uint8_t datatype,void * data);
void UartMsg_Hander(uint8_t data);

#endif
