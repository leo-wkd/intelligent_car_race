#include "Drive.h"

//变量声明

/************一下是根据FreeCars上位机协议修改的，无需改变**************/
uint8 uSendBuf[UartDataNum*2]= {0};
SerialPortType SerialPortRx;
uint8 FreeCarsDataNum=UartDataNum*2;
double UartData[9] = {0};

//函数声明
void push(uint8 chanel,uint16 dat);
void sendDataToScope(void);


/**************************/
/*
轮询法发送一帧数据
消耗时间与数据长度有关
不可以放在中断里面中期性调用
*/
void sendDataToScope(void)
{
    uint8 i,sum=0;

    uart_putchar(UART4,251);
    uart_putchar(UART4,109);
    uart_putchar(UART4,37);

    sum+=(251);      //全部数据加入校验
    sum+=(109);
    sum+=(37);

    for(i=0; i<FreeCarsDataNum; i++)
    {
        uart_putchar(UART4,uSendBuf[i]);
        sum+=uSendBuf[i];         //全部数据加入校验
    }
    uart_putchar(UART4,sum);
}

/*
向某个通道填充数据
adr：通道
date：数据-32768~32767
*/
void push(uint8 chanel,uint16 dat)
{
    uSendBuf[chanel*2]=dat/256;
    uSendBuf[chanel*2+1]=dat%256;
}
/*
模拟产生摄像头赛道数据
IsSingleLine:有人喜欢用单线，比如左中右之一，也有人用双线，同时使用左和右两条线，因此有两种模式
*/
uint8 camLineData[(ROW+1)*2];   //双线模式，要发送两条线

void produceCamRoadData(uint8 line)
{
    if(line == 1)
    {

        for(uint8 i = 0; i < ROW + 1 ; i++) //画中线
        {
            camLineData[i] = 40;            //画定值中线
            camLineData[i + ROW + 1] = Mid[ROW-i];//画中线

//	  if(ROW-i>m)	camLineData[i + ROW + 1] = Mid[ROW-i];//画中线
//	  else			camLineData[i + ROW + 1] = 80;//隐藏无效行数据
        }
//	  camLineData[ROW+1] = 40;
//	  camLineData[ROW+ROW+1] = 40;
    }
    else if(line == 2)
    {
        for(uint8 i = 0; i < ROW + 1 ; i++) //画左右边线
        {
//	  if(ROW-i>=l)	camLineData[i] = Left[ROW-i];//画左边线
//	  else 			camLineData[i] = 80;//隐藏无效行数据
//
//	  if(ROW-i>=r)	camLineData[i + ROW + 1] = Right[ROW-i];//画右边线
//	  else 			camLineData[i + ROW + 1] = 80;//隐藏无效行数据
            camLineData[i] = Left[ROW-i];            //画左边线
            camLineData[i + ROW + 1] = Right[ROW-i];//画右边线
        }
    }
}
/*
轮询法发送一帧数据
消耗时间与数据长度有关
不可以放在中断里面周期性调用
LineData: 保存了摄像头图像处理后的赛道信息
*/
void sendRoadDataToCamViewer(uint8* LineData)
{
    uint8  sum=0;
    uint8 dataNumber = (ROW+1)*2 ;//注意i和dataNumer的数据类型

    uart_putchar(UART4,0xFC); //252
    uart_putchar(UART4,0x08); //008
    uart_putchar(UART4,0xCF); //207
    sum+=(0xFC);      //全部数据加入校验
    sum+=(0x08);
    sum+=(0xCF);

    for(uint8 i=0; i<dataNumber; i++)
    {
        uart_putchar(UART4,LineData[i]);
        sum+=LineData[i];         //全部数据加入校验
    }
    uart_putchar(UART4,sum);
}

//MCU接受数据
void UART3_receive(void)
{
    int16 i,b,d1;
    uint32 d;

    if(uart_query(UART4))//检查是否接收到字符
    {
        uart_querychar(UART4,&SerialPortRx.Data);  //串口查询方式读取一个字节

        if( SerialPortRx.Stack < UartRxBufferLen )
        {
            SerialPortRx.Buffer[SerialPortRx.Stack++] = SerialPortRx.Data;//从串口读取一个数据到缓存

            if(   SerialPortRx.Stack >= UartRxDataLen  //UartRxDataLen个数为一帧
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen]  ==0xff //校验字头
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+1]==0x55
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+2]==0xaa
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+3]==0x10 )
            {
                //double data 9个通道数据校验
                SerialPortRx.Check = 0;
                b = SerialPortRx.Stack - UartRxDataLen; //起始位
                for(i=b; i<SerialPortRx.Stack-1; i++)  //除校验位外的位进行校验
                {
                    SerialPortRx.Check += SerialPortRx.Buffer[i];//校验
                }

                if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
                {
                    //校验成功，进行数据解算
                    for(i = 0; i<9; i++)
                    {
                        d = SerialPortRx.Buffer[b+i*4+4]*0x1000000L + SerialPortRx.Buffer[b+i*4+5]*0x10000L + SerialPortRx.Buffer[b+i*4+6]*0x100L + SerialPortRx.Buffer[b+i*4+7];
                        if(d>0x7FFFFFFF)
                        {
                            d1 = 0x7FFFFFFF - d;
                        }
                        else
                        {
                            d1 = d;
                        }
                        UartData[i]=d1;
                        UartData[i]/=65536.0;
                    }
                    UartDebug();  //转去处理，把受到的数据付给变量
                }
                SerialPortRx.Stack = 0;
            }
            else if(   SerialPortRx.Stack >= UartRxCmdLen //UartRxDataLen个数为一帧
                       && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen]  ==0xff
                       && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+1]==0x55
                       && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+2]==0xaa
                       && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+3]==0x77 )//cmd
            {
                SerialPortRx.Check = 0;
                b = SerialPortRx.Stack - UartRxCmdLen; //起始位
                for(i=b; i<SerialPortRx.Stack-1; i++)  //除校验位外的位进行校验
                {
                    SerialPortRx.Check += SerialPortRx.Buffer[i];//校验
                }
                if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
                {
                    //校验成功
                    UartCmd(UartCmdNum,UartCmdData);//处理接收到的命令，付给MCU命令变量
                }
                SerialPortRx.Stack = 0;
            }
        }
        else
        {
            SerialPortRx.Stack = 0;
        }
    }
}

void UartDebug(void)
{
    push(2,(int16)UartData[0]);	//将数据发送回去观察
    push(3,(int16)UartData[8]);
    sendDataToScope();

    //  PID0Velocity.SetVal = UartData[0];
    //	PID1Velocity.SetVal = UartData[1];
}
/*
命令接收函数
CmdNum：0~255号命令
DATA  ：0~255个命令所对应的命令字
*/
void UartCmd(uint8 CmdNum,uint8 Data)
{

    push(0,CmdNum);	//将数据发送回去观察
    push(1,Data);
    sendDataToScope();

    /*   switch(CmdNum)//cmd number
    {
    case UART_IMAG_TX:
    {
    if(Data)
    UART_IMAGE_TRANSFER=true;
          else
    UART_IMAGE_TRANSFER=false;
    break;
    }
    }		 */
}

/*
发送一幅图像到上位机
*/
void sendCamImgToCamViewer(void)
{
    uart_putchar(UART4,0xFF);//FF,FE,FF,FE四个数表示一幅图像的开始
    uart_putchar(UART4,0xFE);
    uart_putchar(UART4,0xFF);
    uart_putchar(UART4,0xFE);

    for(uint8 i = 0; i<ROW; i++)
        for(uint8 j = 0; j<LINE; j++)
        {
            uint8 data = img[i][j];
            if(data > 0xFD) data = 0xFD; //避开校验位
            uart_putchar(UART4,data);
        }
    uart_putchar(UART4,0xFE);//FE,FE 2个数表示换行
    uart_putchar(UART4,0xFE);
}

