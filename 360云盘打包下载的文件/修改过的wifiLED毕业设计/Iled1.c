#include"stc12c5a60s2.h"
#define uint unsigned int 
#define uchar unsigned char

sbit AddPWM=P1^0;                 //通过P10，P11低电平（按键）加减PWM占空比
sbit CutPWM=P1^1;
void DelayMs(uchar  ms);
void init_PWM();
void Uart_SendData(uchar dat);
void PWM0_change(uchar type,uchar change);
void PWM0_set(void);
uchar code table[]={'1','2','3','4'};
 uchar redclor, blueclor;
					  		  
void DelayMs(uchar ms)            //这个延时可能不对，非关键部分，可自己修改
{
 uint i;
 while(ms--)
 {
  for(i=0;i<850;i++);
 }
 
}

void PWM0_set(void) //直接设置占空比
{
 
 CCAP0L=blueclor;   //  蓝色
 CCAP0H=blueclor;
 CCAP1L=redclor;					    
 CCAP1H=redclor;
}

void init_PWM()
{
 CCON=0X00;
 CH=0;
 CL=0;
 CMOD=0X08;        //0X00：以系统时钟/12为时钟源，0X02：系统时钟/2，0x08：系统时钟/8   红色
 CCAPM1=0x42;                 //PCA_PWM0=0x00;//控制占空比的第九位为0
 CCAPM0=0X00;      //0X42：8位PWM?P1.3输出,无中断；0X53：8位PWM输出，下降沿产生中断；0X63：上升沿产生中断；0X73：跳变沿产生中断
 CR=0;             //计时器开始工作
 //PWM0_set(0X00,0x00);   //起始占空比，0XC0:占空比为25%，0X80:占空比为50%，0X40:占空比为75%?
}

void UartInit(void)		//115200bps@11.0592MHz
{
	PCON &= 0x7f;  //波特率不倍速
   SCON = 0x50;  //8位数据,可变波特率
   BRT = 0xFD;      //设定独立波特率发生器重装值
   AUXR |= 0x04;  //独立波特率发生器时钟为Fosc,即1T
   AUXR |= 0x01;  //串口1选择独立波特率发生器为波特率发生器
   AUXR |= 0x10;  //启动独立波特率发生器
}

void main()
{	
    uint RECV,a;
    UartInit();
	init_PWM();
	   P2=0X00;
	   P1=0X00;
	   CCAPM1=0x00;                 //PCA_PWM0=0x00;//控制占空比的第九位为0
       CCAPM0=0X00;
	   redclor=0xff;
	   blueclor=0xff;
	   PWM0_set();
	   
/*单片机串口接收监测程序*/
    while(1)
    {
      if(RI==1)
	  {
	  
	    RECV=SBUF ;
//	    if(RECV=='1')
//	    {
//	      CR = 1 ;
//		  P2=0X00;
//	      //SBUF=0;
//	    }
	    if(RECV=='0')
        {
	      CR=0;
		  P2=0X00;
		  P1=0X00;
		  CCAPM1=0x00;
		  CCAPM0=0x00;
	    }

	
		if(RECV=='1')
        {
	      CR=1;
		  P2=0X00;
		  blueclor=0xef;
		  PWM0_set();
		  CCAPM0=0x42;
	    }
		if(RECV=='2')
        {
	      CR=1;
		  P2=0X00;
		  blueclor=0xaf;
		  PWM0_set();
		  CCAPM0=0x42;
	    }
		if(RECV=='3')
        {
	      CR=1;
		  P2=0X00;
		  blueclor=0x7f;
		  PWM0_set();
		  CCAPM0=0x42;
	    }
		if(RECV=='4')
        {
	      CR=1;
		  P2=0X00;
		  blueclor=0x3f;
		  PWM0_set();
		  CCAPM0=0x42;
	    }
		if(RECV=='5')
        {
	      CR=1;
		  P2=0X00;
		  redclor=0xef;
		  PWM0_set();
		  CCAPM1=0x42;
	    }
		if(RECV=='6')
        {
	      CR=1;
		  P2=0X00;
		  redclor=0xaf;
		  PWM0_set();
		  CCAPM1=0x42;
	    }
		if(RECV=='7')
        {
	      CR=1;
		  P2=0X00;
		  redclor=0x8f;
		  PWM0_set();
		  CCAPM1=0x42;
	    }
		if(RECV=='8')
        {
	      CR=1;
		  P2=0X00;
		  redclor=0x4f;
		  PWM0_set();
		  CCAPM1=0x42;
	    }
		if(RECV=='9')
        {
	      CR=1;
		  P2=0X00;
		  redclor=0x1f;
		  PWM0_set();
		  CCAPM1=0x42;
	    }

		if(RECV=='W')
        {
	      CR=0;
		  P2=0X04;
		  redclor=0xff;
		  blueclor=0xff;
		  CCAPM1=0x00;
		  CCAPM0=0x00;
	    }
	    RI=0 ;
	
	}   

   }

}
