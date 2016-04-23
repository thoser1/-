#include"stc12c5a60s2.h"
#define uint unsigned int 
#define uchar unsigned char

sbit AddPWM=P1^0;                 //ͨ��P10��P11�͵�ƽ���������Ӽ�PWMռ�ձ�
sbit CutPWM=P1^1;
void DelayMs(uchar  ms);
void init_PWM();
void Uart_SendData(uchar dat);
void PWM0_change(uchar type,uchar change);
void PWM0_set(void);
uchar code table[]={'1','2','3','4'};
 uchar redclor, blueclor;
					  		  
void DelayMs(uchar ms)            //�����ʱ���ܲ��ԣ��ǹؼ����֣����Լ��޸�
{
 uint i;
 while(ms--)
 {
  for(i=0;i<850;i++);
 }
 
}

void PWM0_set(void) //ֱ������ռ�ձ�
{
 
 CCAP0L=blueclor;   //  ��ɫ
 CCAP0H=blueclor;
 CCAP1L=redclor;					    
 CCAP1H=redclor;
}

void init_PWM()
{
 CCON=0X00;
 CH=0;
 CL=0;
 CMOD=0X08;        //0X00����ϵͳʱ��/12Ϊʱ��Դ��0X02��ϵͳʱ��/2��0x08��ϵͳʱ��/8   ��ɫ
 CCAPM1=0x42;                 //PCA_PWM0=0x00;//����ռ�ձȵĵھ�λΪ0
 CCAPM0=0X00;      //0X42��8λPWM?P1.3���,���жϣ�0X53��8λPWM������½��ز����жϣ�0X63�������ز����жϣ�0X73�������ز����ж�
 CR=0;             //��ʱ����ʼ����
 //PWM0_set(0X00,0x00);   //��ʼռ�ձȣ�0XC0:ռ�ձ�Ϊ25%��0X80:ռ�ձ�Ϊ50%��0X40:ռ�ձ�Ϊ75%?
}

void UartInit(void)		//115200bps@11.0592MHz
{
	PCON &= 0x7f;  //�����ʲ�����
   SCON = 0x50;  //8λ����,�ɱ䲨����
   BRT = 0xFD;      //�趨���������ʷ�������װֵ
   AUXR |= 0x04;  //���������ʷ�����ʱ��ΪFosc,��1T
   AUXR |= 0x01;  //����1ѡ����������ʷ�����Ϊ�����ʷ�����
   AUXR |= 0x10;  //�������������ʷ�����
}

void main()
{	
    uint RECV,a;
    UartInit();
	init_PWM();
	   P2=0X00;
	   P1=0X00;
	   CCAPM1=0x00;                 //PCA_PWM0=0x00;//����ռ�ձȵĵھ�λΪ0
       CCAPM0=0X00;
	   redclor=0xff;
	   blueclor=0xff;
	   PWM0_set();
	   
/*��Ƭ�����ڽ��ռ�����*/
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
