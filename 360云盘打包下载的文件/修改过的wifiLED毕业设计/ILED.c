#include"stc12c5a60s2.h"

#define uchar unsigned char 
#define uint  unsigned int
#define  RIN   P2^3
#define  GIN   P2^2

//sfr  CCON =0xD8;//PCA控制寄存器?
//sbit CCF0 =CCON^0;
//sbit CCF1 =CCON^1;
//sbit CR   =CCON^6;
//sbit CF   =CCON^7;
//sfr CMOD  =0xD9;//PCA工作模式寄存器
//sfr CL    =0xE9;//PCA?base?timer?LOW??
//sfr CH    =0xF9;//PCA?base?timer?HIGH??
//sfr CCAPM0=0xDA;//PCA模块0的比较/捕获寄存器??
//sfr CCAP0L=0xEA;//PCA?module-0?capture?register?LOW??
//sfr CCAP0H=0xFA;//PCA?module-0?capture?register?HIGH??
//sfr CCAPM1=0xDB;//PCA?module-1?mode?register??
//sfr CCAP1L=0xEB;//PCA?module-1?capture?register?LOW??
//sfr CCAP1H=0xFB;//PCA?module-1?capture?register?HIGH??
sfr PCAPWM0=0xf2;
sfr PCAPWM1=0xf3;

void PWMINIT(void);//PWM初值化
void PWMDR(uchar x,uchar y); //调整占空比；x,y值越小正占空比越大?
void delay_50us(uint t);
void delay_50ms(uchar t);
void delay_1ms(uchar b);
void delay_50us(uint t)
{
 uchar j;
 for(;t>0;t--)
 for(j=19;j>0;j--);
}
void delay_1ms(uchar b) 
{
 uchar i;
 i=125;
 while(b--)
 {
  while(i--);
 }
 
}

void delay_50ms(uchar t)
{
 uint j;
 for(;t>0;t--)
 for(j=6245;j>0;j--);
 }
char code PWMNUM[]={0x00,0x08,0x10,0x18,0x22,0x30,0x38,0x40,0x48,0x50,0x60,0x60,0x68,0x70,0x78,0x80,0x88,0x90,0x98,0xa0,0xa8,0xb0,0xb8,0xc0,0xc8,0xff};
void PWMINIT(void)
{
 CCON =0;//Initial?PCA?control?register??
 CL   =0;//Reset?PCA?base?timer??????CH?=?0;??
 CMOD =0x02;//Set?PCA?timer?clock?source?as?Fosc/2???
 CCAPM0=0x42;//PCA?module-0?work?in?8-bit?PWM?mode
 CCAPM1=0x42;//PCA?module-1?work?in?8-bit?PWM?mode??
 CR=1;//PCA?timer?start?run

}

void PWMDR(uchar x,uchar y)//x,y值越小正占空比越大
{
 CCAP0H=CCAP0L=PWMNUM[x];//P1.3输出?? 红
 CCAP1H=CCAP1L=PWMNUM[y];//P1.4输出   黄			   //1是红  
}
void main()
{
 PWMINIT();
 while(1)
 {
  PWMDR(25,0);
  				  //当p1为ff p2为00时  灯不亮   
  P2=0Xf4;
 }
  
 
}


#define U8 unsigned char
#define U8 unsigned char
#define U16 unsigned int
void DelayMs(U8 ms);
void PWM_clock(U8 clock);
void PWM_start(U8 module,U8 mode);
////////////////////// 延时子程序/////////////////////////////
void DelayMs(U8 ms) //在11.0592M晶振下，stc10f系列（单周期指令）的ms级延时
{      
	U16 i;
	while(ms--)
	{
		for(i = 0; i < 850; i++);
	}
}