#include"Getline.h"

uint8 start_flg = 0;
uint8 tiaopbiandian = 0;
uint8 stop_flg = 0;
uint8 sstop_flg = 0;
uint8 break_flg = 0;
int32 stop_distance = 0;
uint32 start_time = 0;
uint8 qipao_startrow;
uint8 sa = 0;
uint8 endd= 0;
uint8 qipao_endrow;
void stop();
void get_startline()
{
    tiaopbiandian = 0;
    qipao_startrow = 0;
    qipao_endrow = 0;
    if(start_time<200&&run_flg) start_time++; //�����߼���ʱ
    if(l>=55||r>=55||Slope_distance!=0)  goto end;
    for(uint8 i =59 ; i>((l>r?l:r)+2); i--)
    {

        for(uint8 j =Left[i]; j<Right[i]; j++)
        {
            if(img[i][j]==BLACK&&img[i][j+1]==WHITE) //�������������
                tiaopbiandian++;
        }
        if(tiaopbiandian>=6)
        {
            start_flg = 1;
            qipao_startrow = i;
            break;
        }
        start_flg = 0;
        tiaopbiandian = 0;
    }
    if(qipao_startrow!=0)
    {
        for(uint8 i = qipao_startrow;i>((l>r?l:r)+2);i--)
        {
        for(uint8 j = Left[i]; j<Right[i]; j++)
        {
            if(img[i][j]==BLACK&&img[i][j+1]==WHITE) //�������������
                tiaopbiandian++; 
        }
        if(tiaopbiandian<=3)
        {
           qipao_endrow = i;
           goto  tis;
        }
         tiaopbiandian = 0;
        }
       
  }
    tis: if(qipao_startrow!=0&&qipao_endrow!=0&&sstop_flg)
         {
          if(qipao_startrow>=55) qipao_startrow =55;
          if(qipao_endrow<5)  qipao_endrow = 5;
          for(uint8 i = qipao_startrow+4;i>=qipao_endrow-2;i--)
            {
           for(uint8 j = Left[i];j<40;j++)
              {
              if(img[i][j]==BLACK&&img[i][j+1]==WHITE)
                {
                    sa = j+1;
                    break;
                }
               }
           for(uint8 j =Right[i];j>40;j-- )
              {
                if(img[i][j]==BLACK&&img[i][j-1]==WHITE)
                 {
                    endd = j+1;
                    break;
                  }
              }
            for(uint8 k = sa;k<endd;k++)
             {
                 img[i][k] = WHITE;

              }
            }
       }
    
    if(start_flg ==1&&start_time>=200)  //������������ ���� ʱ������
    {

        break_flg = 1;
    }
    else if(start_flg==1)  //������Ϊ�ڷ����׶�
    {
        sstop_flg = 1;

    }
    else if(start_flg==0)
    {
        sstop_flg = 0;       //��������־λ����
    }
 end:;
}
void stop()
{
   if(Double_Car_Mode)
   { 
     if(break_flg==1&&Car_State==QIAN)
      
     {
       int32 dis = 0;
       uint8 testflg = 2;
       car_send(TYPE_FLAG,&testflg);
       car_send(TYPE_FLAG,&testflg);
       while(1)
    {
        img_extract(&img[0][0],imgbuff,CAMERA_SIZE);//��ѹ����ά����
        GetLine();
        Cacl_Error();
        Rudder_ctrl();
        dis+=speed_ave;
        if(dis>=25000)
        {
          car.targetspeed = 0;
        }
        Diff_Speed();
        Speed_Get();
        Speed_Ctrl();
        OLED();
        while(Pic_complete == 1);
        while(Pic_complete == 0);
    }
    } 
     else if(break_flg==1&&flag==2)
    {
       int32 dis = 0;
           while(1)
    {
        img_extract(&img[0][0],imgbuff,CAMERA_SIZE);//��ѹ����ά����
        GetLine();
        Cacl_Error();
        Rudder_ctrl();
        dis+=speed_ave;
        if(dis>=25000)
        {
          car.targetspeed = 0;
        }
        Diff_Speed();
        Speed_Get();
        Speed_Ctrl();
        OLED();
        while(Pic_complete == 1);
        while(Pic_complete == 0);
    }

    }
    
   }
}
uint8 qian_flg = 0;
void finaqianche()
{
    uint8 black = 0;
    uint8 dis = 0;
    qian_flg = 0;
    for(uint8 i = 59;i>(l>r?l:r);i++)
  
    { 
      for(uint8 j = Left[i]+2;j<Right[i]-2;j++)
   {
      if(img[i][j]==BLACK) black++;
     
    }
       if(black>=8&&dis>=10) 
         {
          qian_flg = 1;
           break;
          }
       black = 0;
    }
}
void qipao_stop()
{
#if Double_Car_Mode
    if(Car_State==QIAN)  //˫�� ǰ�� ������ �߼�
    {
       int32 sssstop_distance = 0;
        uint8 put_flg = 0;
        int32 time = 0;
        uint8 fflg = 0;
        uint8 ffflg = 0;
        if(break_flg==1)
        {
           pit_time_start(PIT3);
           
            while(1)
            {
                time = pit_time_get_ms(PIT3);
                if(time>3000&&flag!=7&&!ffflg) 
                {
                  fflg = 1;
                  pit_close(PIT3);
                }
                if(flag==88)  ffflg = 1; 
                if(flag!=7&&put_flg<5)
               {
                uint8  testflag = 8;
                car_send(TYPE_FLAG,&testflag); //ǰ���Ѿ���⵽������ ���͸��� ��־λ8
                car_send(TYPE_FLAG,&testflag); //ǰ���Ѿ���⵽������ ���͸��� ��־λ8
                put_flg ++; 
               }
                img_extract(&img[0][0],imgbuff,CAMERA_SIZE);//��ѹ����ά����
                GetLine();
                Cacl_Error();
                Rudder_ctrl();
                Speed_Get();
                if(flag!=7)	//û���յ� ��־λ7 ��Ϊ��û�е���
                    {
                    
                    car.targetspeed = 0;
                    }
                else if(flag==7) car.targetspeed = 1500; //�յ� ��־λ7 ��Ϊ�󳵵���
                if(fflg)  flag = 7;
                if(flag==7)
                {
                    sssstop_distance+=speed_ave;//��ʼ�������
                }
                if(sssstop_distance>=20000) //�������ײ���
                {
                    car.targetspeed = 0;
                }
              
                Diff_Speed();
                Speed_Ctrl();
                OLED();
                while(Pic_complete == 1);
                while(Pic_complete == 0);
            }
        }
    }
    else
    {
        if(flag==8)  //˫�� �� ������ �߼�
        {
            uint8 put_flg = 0;
            int32 sssstop_distance;
            uint8 black = 0;
            uint8 test_flg = 88;
            car_send(TYPE_FLAG,&test_flg);
            car_send(TYPE_FLAG,&test_flg);
            while(1)
            {
                img_extract(&img[0][0],imgbuff,CAMERA_SIZE);//��ѹ����ά����
                GetLine();
                Cacl_Error();
                Rudder_ctrl();
                Speed_Set();
                Speed_Get();
                if(qian_flg==0)
               {
                for(uint8 i = 59;i>(l>r?l:r);i--)
   
               { 
                  for(uint8 j = Left[i]+2;j<Right[i]-2;j++)
                {
                   if(img[i][j]==BLACK) black++;
     
                 }
                    if(black>=5&&i>=10) 
                {
                      qian_flg = 1;
                      break;
                }
                     black = 0;
                }
                }
             /* if(Distance<60&&Distance_Still_flg!=1) //�󳵼�⵽ǰ���ľ���С��80 ���� �����ڸ���
                {
                    uint8 testflag = 7;   //���ͱ�־λ7
                    car_send(TYPE_FLAG,&testflag);
                    car_send(TYPE_FLAG,&testflag);
                    put_flg = 1;
                    gpio_set(PTA5,1);
                }*/
                if( ((put_flg<=10&&put_flg!=0)||qian_flg||(Distance<120&&Distance_Still_flg!=1)))
                 {
                    uint8 testflag = 7;   //���ͱ�־λ7
                    car_send(TYPE_FLAG,&testflag);
                    car_send(TYPE_FLAG,&testflag);                 
                    put_flg++;
                    
                 }
                if(put_flg>=1)
                {
                    car.targetspeed = 1200;//
                    sssstop_distance+=speed_ave;//��ʼ�������

                }
                  uint16 testspeed = (uint16)car.targetspeed;
                  car_send(TYPE_SPEED,&testspeed);
                  if(sssstop_distance>=45000) //�������ײ���
                {
                    car.targetspeed = 0;
                }
          
                Diff_Speed();
                Speed_Ctrl();
                OLED();
                while(Pic_complete == 1);
                while(Pic_complete == 0);

            }
        }
    }
#endif 
}