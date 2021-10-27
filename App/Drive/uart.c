#include "Drive.h"

//��������

/************һ���Ǹ���FreeCars��λ��Э���޸ĵģ�����ı�**************/
uint8 uSendBuf[UartDataNum*2]= {0};
SerialPortType SerialPortRx;
uint8 FreeCarsDataNum=UartDataNum*2;
double UartData[9] = {0};

//��������
void push(uint8 chanel,uint16 dat);
void sendDataToScope(void);


/**************************/
/*
��ѯ������һ֡����
����ʱ�������ݳ����й�
�����Է����ж����������Ե���
*/
void sendDataToScope(void)
{
    uint8 i,sum=0;

    uart_putchar(UART4,251);
    uart_putchar(UART4,109);
    uart_putchar(UART4,37);

    sum+=(251);      //ȫ�����ݼ���У��
    sum+=(109);
    sum+=(37);

    for(i=0; i<FreeCarsDataNum; i++)
    {
        uart_putchar(UART4,uSendBuf[i]);
        sum+=uSendBuf[i];         //ȫ�����ݼ���У��
    }
    uart_putchar(UART4,sum);
}

/*
��ĳ��ͨ���������
adr��ͨ��
date������-32768~32767
*/
void push(uint8 chanel,uint16 dat)
{
    uSendBuf[chanel*2]=dat/256;
    uSendBuf[chanel*2+1]=dat%256;
}
/*
ģ���������ͷ��������
IsSingleLine:����ϲ���õ��ߣ�����������֮һ��Ҳ������˫�ߣ�ͬʱʹ������������ߣ����������ģʽ
*/
uint8 camLineData[(ROW+1)*2];   //˫��ģʽ��Ҫ����������

void produceCamRoadData(uint8 line)
{
    if(line == 1)
    {

        for(uint8 i = 0; i < ROW + 1 ; i++) //������
        {
            camLineData[i] = 40;            //����ֵ����
            camLineData[i + ROW + 1] = Mid[ROW-i];//������

//	  if(ROW-i>m)	camLineData[i + ROW + 1] = Mid[ROW-i];//������
//	  else			camLineData[i + ROW + 1] = 80;//������Ч������
        }
//	  camLineData[ROW+1] = 40;
//	  camLineData[ROW+ROW+1] = 40;
    }
    else if(line == 2)
    {
        for(uint8 i = 0; i < ROW + 1 ; i++) //�����ұ���
        {
//	  if(ROW-i>=l)	camLineData[i] = Left[ROW-i];//�������
//	  else 			camLineData[i] = 80;//������Ч������
//
//	  if(ROW-i>=r)	camLineData[i + ROW + 1] = Right[ROW-i];//���ұ���
//	  else 			camLineData[i + ROW + 1] = 80;//������Ч������
            camLineData[i] = Left[ROW-i];            //�������
            camLineData[i + ROW + 1] = Right[ROW-i];//���ұ���
        }
    }
}
/*
��ѯ������һ֡����
����ʱ�������ݳ����й�
�����Է����ж����������Ե���
LineData: ����������ͷͼ������������Ϣ
*/
void sendRoadDataToCamViewer(uint8* LineData)
{
    uint8  sum=0;
    uint8 dataNumber = (ROW+1)*2 ;//ע��i��dataNumer����������

    uart_putchar(UART4,0xFC); //252
    uart_putchar(UART4,0x08); //008
    uart_putchar(UART4,0xCF); //207
    sum+=(0xFC);      //ȫ�����ݼ���У��
    sum+=(0x08);
    sum+=(0xCF);

    for(uint8 i=0; i<dataNumber; i++)
    {
        uart_putchar(UART4,LineData[i]);
        sum+=LineData[i];         //ȫ�����ݼ���У��
    }
    uart_putchar(UART4,sum);
}

//MCU��������
void UART3_receive(void)
{
    int16 i,b,d1;
    uint32 d;

    if(uart_query(UART4))//����Ƿ���յ��ַ�
    {
        uart_querychar(UART4,&SerialPortRx.Data);  //���ڲ�ѯ��ʽ��ȡһ���ֽ�

        if( SerialPortRx.Stack < UartRxBufferLen )
        {
            SerialPortRx.Buffer[SerialPortRx.Stack++] = SerialPortRx.Data;//�Ӵ��ڶ�ȡһ�����ݵ�����

            if(   SerialPortRx.Stack >= UartRxDataLen  //UartRxDataLen����Ϊһ֡
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen]  ==0xff //У����ͷ
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+1]==0x55
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+2]==0xaa
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+3]==0x10 )
            {
                //double data 9��ͨ������У��
                SerialPortRx.Check = 0;
                b = SerialPortRx.Stack - UartRxDataLen; //��ʼλ
                for(i=b; i<SerialPortRx.Stack-1; i++)  //��У��λ���λ����У��
                {
                    SerialPortRx.Check += SerialPortRx.Buffer[i];//У��
                }

                if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
                {
                    //У��ɹ����������ݽ���
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
                    UartDebug();  //תȥ�������ܵ������ݸ�������
                }
                SerialPortRx.Stack = 0;
            }
            else if(   SerialPortRx.Stack >= UartRxCmdLen //UartRxDataLen����Ϊһ֡
                       && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen]  ==0xff
                       && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+1]==0x55
                       && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+2]==0xaa
                       && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+3]==0x77 )//cmd
            {
                SerialPortRx.Check = 0;
                b = SerialPortRx.Stack - UartRxCmdLen; //��ʼλ
                for(i=b; i<SerialPortRx.Stack-1; i++)  //��У��λ���λ����У��
                {
                    SerialPortRx.Check += SerialPortRx.Buffer[i];//У��
                }
                if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
                {
                    //У��ɹ�
                    UartCmd(UartCmdNum,UartCmdData);//������յ����������MCU�������
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
    push(2,(int16)UartData[0]);	//�����ݷ��ͻ�ȥ�۲�
    push(3,(int16)UartData[8]);
    sendDataToScope();

    //  PID0Velocity.SetVal = UartData[0];
    //	PID1Velocity.SetVal = UartData[1];
}
/*
������պ���
CmdNum��0~255������
DATA  ��0~255����������Ӧ��������
*/
void UartCmd(uint8 CmdNum,uint8 Data)
{

    push(0,CmdNum);	//�����ݷ��ͻ�ȥ�۲�
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
����һ��ͼ����λ��
*/
void sendCamImgToCamViewer(void)
{
    uart_putchar(UART4,0xFF);//FF,FE,FF,FE�ĸ�����ʾһ��ͼ��Ŀ�ʼ
    uart_putchar(UART4,0xFE);
    uart_putchar(UART4,0xFF);
    uart_putchar(UART4,0xFE);

    for(uint8 i = 0; i<ROW; i++)
        for(uint8 j = 0; j<LINE; j++)
        {
            uint8 data = img[i][j];
            if(data > 0xFD) data = 0xFD; //�ܿ�У��λ
            uart_putchar(UART4,data);
        }
    uart_putchar(UART4,0xFE);//FE,FE 2������ʾ����
    uart_putchar(UART4,0xFE);
}

