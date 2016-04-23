#include <c8051f360.h>
#include <stdio.h>
#include<math.h>
#include <absacc.h>

#define WDATADDR XBYTE[0XC009]				//LCD写数据地址
#define RDATADDR XBYTE[0XC00B]				//LCD读数据地址
#define WCOMADDR XBYTE[0XC008]				//LCD写命令地址
#define RCOMADDR XBYTE[0XC00A]				//LCD读命令地址
#define KEYCS 	 XBYTE[0XC00C]				//键盘片选地址
#define T_C 	 40
sbit LCD_RST=P3^0;
sbit CHUFA=P0^6;


unsigned char    F_DISP[]={"00000%"};
unsigned char    F_DISPLOW[]={"00000HZ    "};
unsigned char    F_DISPLOWHIGH[]={"00000HZ   "}  ;
unsigned char    F_DISPHIGH[]={"0000HZ     "} ;
unsigned char    F_DISPHIGHONE[]={"00000 kHZ"};
unsigned char code TAB_WORD[]={"信号频率为"};
unsigned char  F_DISPHIGHTHREE[]={"00000 MHZ"};
unsigned char   count[11]={ 0,0,0,0,0,0,0,0,0,0,0};			  
unsigned long n=0;
unsigned long m=0;
unsigned char fp;
unsigned long f;
unsigned char f1;
bit flag=0;


unsigned char key_num=0xff;					//存键号

void OSC_INIT (void)			//内部振荡器初始化
{
	SFRPAGE=0X0F;
	OSCICL=OSCICL+5;
	OSCICN=0XC3;
	CLKSEL=0X30;
	SFRPAGE=0;

}
//********************************************
void IO_INIT(void)					   //I/O端口初始化		，1为数字，0为模拟，1是推拉式，1是被开关跳过，0是不被交叉开关跳过。
{
	SFRPAGE=0X0F;
	P0MDIN=0Xe7;					//P0.3-P0.4设置为模拟量输入
	P0MDOUT=0X83;					//P0.0，P0.1，P0.7推拉式输出
	P0SKIP=0XF9;					//P0.1，P0.2不被交叉开关跳过

	P1MDIN=0XFF;					  //   P1数字量输入
	P1MDOUT=0XFF;						  //P1推拉式输出
	P1SKIP=0XFF;				   //P1交叉开关跳过

	P2MDIN=0XFE;
	P2MDOUT=0XFF;
	P2SKIP=0XFF;

	P3MDIN=0XFF;
	P3MDOUT=0XFF;
	P3SKIP=0XF9; 			//0xfd，增加P3.2作T1输入

	P4MDOUT=0XFF;
	
	XBR0=0X09;
	XBR1=0Xe0;				//0xc0,增加T1
	SFRPAGE=0X0;
}
//********************************************
void XRAM_INIT(void)		   //外部数据存储器接口初始化
{
	SFRPAGE=0X0F;
	EMI0CF=0X07;
	SFRPAGE=0;
}
//********************************************
void SMB_INIT(void)
{
	SMB0CF=0XC1;

}
//********************************************
void UART_INIT(void)
{
	  	SCON0=0X0;
}
//********************************************
void DAC_INIT(void)					//IDA0控制寄存器
{
	IDA0CN=0XF2;					  //写IDA0H触发DAC更新
}
//********************************************
void ADC_INIT(void)
{
   	REF0CN=0;		 		//VDD为基准
	AMX0P=0X08;		 		//正端接P20
	AMX0N=0X1F;				//负端接GND
	ADC0CF=0X2C;	 		//左对齐，转换时钟2MHZ
	ADC0CN=0X80;	 		//写ADOBUSY启动AD
}
//********************************************
void INT0_INIT(void)
{
	IT01CF=0X05;				//P0.5为INT0
	IT0=1;						//下降沿触发
}
//********************************************
void TIMER_INIT(void)			 //定时/计数器初始化
{
	TMOD=0x51;					//T0、T1方式1,T1计数方式
	CKCON=0; 					//系统时钟12分频

	TL0=0x66;					
	TH0=0x3e;				

	TL1=0X0;
	TH1=0X0;					//计数器清0
	
	fp=T_C;

	TMR2CN=0X04;				//16位自动重装
	TMR2RLL=0XF0;				//10MS
	TMR2RLH=0XD8;

	TMR3CN=0X0C;				//双8位自动重装入，系统时钟1/12
	TMR3RLL=0XE0;				//定时100us
	TMR3RLH=0XFF;

	TR0=1;
	TR1=1;
}
//***********************************************
void PCA_INIT(void)
{
	PCA0CN=0X40;				//允许PCA计数器、定时器
	PCA0MD=0;					//禁止看门狗定时器
}
//***********************************************
void INT_INIT(void)
{
	EX0=1;						//INIT0，键盘
	PX0=0;						//INT0为低优先级
	ET0=1;						//T0
	ET1=1;	 					//T1
	ET2=0;						//T2
	EIE1=0X0;					//0X08,允许ADC中断
	ES0=0;						//uart
	EA=1;

	

}
//**************************************************

void Init_device(void) 
{
	OSC_INIT();
	IO_INIT();
	XRAM_INIT();
	SMB_INIT();
	UART_INIT();
	DAC_INIT();
	ADC_INIT();
	INT0_INIT();
	TIMER_INIT();
	PCA_INIT();
	INT_INIT();
}
//**************************************************
//--------------------------------------------------------
void LCD_REST(void)
{
	int i;
	LCD_RST=0;
	for(i=0;i<255;i++);
	LCD_RST=1;
}
//********************************************************
void LCD_WC(unsigned char command)				//LCD写命令
{
	while(RCOMADDR&0X80);		                                                                                                                                                                                                                         
	WCOMADDR=command;
}
//********************************************************
void LCD_INIT(void)							   //LCD初始化
{
	LCD_WC(0X30);								//设为基本命令集
	LCD_WC(0X01); 	
	LCD_WC(0X02);								//将DDRAM填满20H，并设定DDRAM地址计数器为0
	LCD_WC(0X0C);								//开整体显示
}
//***********************************************************

void LCD_WD(unsigned char d)					//LCD写数据
{
	while(RCOMADDR&0X80);
	WDATADDR=d;
}
//**********************************************************
void LCD_HZ(unsigned char x,unsigned char temp[])				//显示一行字符
{
   int i=0;
   LCD_WC(x);												   //x代表位置，=0x80对应左上角
   while(temp[i]!=0)
	 {
		LCD_WD(temp[i]);
		i++;
	}
}
//********************************************************
void LCD_BYTE(unsigned char x,unsigned char temp)				//显示一行字符
{
   LCD_WC(x);												   //x代表位置，=0x80对应左上角
   LCD_WD(temp);
}


//*********************************************************
void LCD_CLR(void) 								//LCD清屏
{
 	  LCD_WC(0X01);
}
//********************************************************
void KEY_INIT0(void) interrupt 0
{
  key_num=KEYCS&0x0f;
 
  
} 
//*****T0中断服务***************************************
void  TT0_INT0(void) interrupt 1
{
    int j=0;
	TL0=0x66;						//0Xb0;
	TH0=0x3d;						//0X3c;每单位0.5微秒*50000*40
 	fp--;
	    if(fp) return;
        TR1=0;
		fp=T_C;                      //1s
        f=65536*f1+256*TH1+TL1;
		if(n==0)
		{
		count[n%11]=f;
		}
		else
		{
		if(abs(count[n%11-1]-f)>=10)
		{	  
		  for(j=0;j<=10;j++)
		  {
		   count[j]=f;
		  }
	    }
		  else
		       {
			     count[n%11]=f;
			    }
		}

		n++;
        flag=1;
        TH1=0;
        TL1=0;
        f1=0;
		TR1=1;
     }
//******************************************



void TT1_INT1(void ) interrupt 3
{
f1++;
}

//*******************************************
void  tolHZ(float s1)
{  int term;
   term=(int)(s1*100);

F_DISPLOW[0]=term/1000%10+0x30;
F_DISPLOW[1]=term/100%10+0x30;
F_DISPLOW[2]=0x2E;
F_DISPLOW[3]=term/10%10+0x30;
F_DISPLOW[4]=term%10+0x30;
}
//********************************************
void  tofHZ(void)
{
   
   
   F_DISPLOWHIGH[0]=f/100%10+0x30;
   F_DISPLOWHIGH[1]=f/10%10+0x30;
   F_DISPLOWHIGH[2]=f%10+0x30;
   F_DISPLOWHIGH[3]=0x2E;
   F_DISPLOWHIGH[4]=0x30;
 }
 //********************************************
 void  toHZ(void)
 {
   
   F_DISPHIGH[0]=f/1000%10+0x30;
   F_DISPHIGH[1]=f/100%10+0x30;
   F_DISPHIGH[2]=f/10%10+0x30;
   F_DISPHIGH[3]=f%10+0x30;
   }
  //*******************************************
  void toKHZ(void)
  {
    if(f>=10000&&f<=99999)
	{
   F_DISPHIGHONE[0]=f/10000%10+0x30;
   F_DISPHIGHONE[1]=f/1000%10+0x30;
   F_DISPHIGHONE[2]=0x2E;
   F_DISPHIGHONE[3]=f/100%10+0x30;
   F_DISPHIGHONE[4]=f/10%10+0x30;
   }
   else
    {   F_DISPHIGHONE[0]=f/100000%10+0x30;
	F_DISPHIGHONE[1]=f/10000%10+0x30;
	F_DISPHIGHONE[2]=f/1000%10+0x30;
	F_DISPHIGHONE[3]=0x2E;
	F_DISPHIGHONE[4]=f/100%10+0x30;
	}
   }
   //******************************************


	void toMHZ(void)
   {
	F_DISPHIGHTHREE[0]=f/1000000%10+0x30;
	F_DISPHIGHTHREE[1]=0x2E;
	F_DISPHIGHTHREE[2]=f/100000%10+0x30;
	F_DISPHIGHTHREE[3]=f/10000%10+0x30;
	F_DISPHIGHTHREE[4]=f/1000%10+0x30;
	}
	//********************************************
 main()  
{
    int xdata flag1=0;
	float  mean = 0;
	int i;
	Init_device();
	LCD_REST();
	LCD_INIT();
 
 	LCD_REST();
	LCD_INIT();

	f=0;
	f1=0;

  while(1)
 {  
  	 LCD_HZ(0x80,"简易频率计");
	LCD_HZ(0x90, "设计：林先娜");
    if(flag)
   {
	 if(f>=10&&f<=99)
    	{
		  
    	  mean=(count[0]+count[1]+count[2]+count[3]+count[4]+count[5]+count[6]+count[7]+count[8]+count[9]+count[10])/11;			//消抖
    	  tolHZ(mean);
    	  LCD_HZ(0x88,TAB_WORD);
    	  LCD_HZ(0x98,F_DISPLOW);
          flag=0;
    	 }
	   else if(f>=100&&f<= 999)
       {
    
		 tofHZ();	 
		 LCD_HZ(0x88,TAB_WORD);
		 LCD_HZ(0x98,F_DISPLOWHIGH);
		 flag=0;
       }
	   else if (f>=1000&&f<=9999)
	   {
	      toHZ();	   
		  LCD_HZ(0x88,TAB_WORD);
		  LCD_HZ(0x98,F_DISPHIGH);
		  flag=0;
	   }
	   else if(f>=10000&&f<=99999)
	   {
    	  toKHZ();
		  LCD_HZ(0x88,TAB_WORD);
		  LCD_HZ(0x98,F_DISPHIGHONE);
		  flag=0;
	   }
	   else if(f>=100000&&f<=999999)
       {
	    toKHZ();
	    LCD_HZ(0x88,TAB_WORD);
	    LCD_HZ(0x98,F_DISPHIGHONE);
	    flag=0;
		}
		else
		{
		toMHZ();
		LCD_HZ(0x88,TAB_WORD);
		LCD_HZ(0x98,F_DISPHIGHTHREE);
		flag=0;
		}

     }	
}
}