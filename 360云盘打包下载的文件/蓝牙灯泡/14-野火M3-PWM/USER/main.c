/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：定时器TIM3产生四路PWM波输出。
 *           - PA.06: (TIM3_CH1)
 *           - PA.07: (TIM3_CH2)
 *           - PB.00: (TIM3_CH3)
 *           - PB.01: (TIM3_CH4) 
 *           TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
 *           TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
 *           TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
 *           TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
 *       
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "pwm_output.h"
#include "stdlib.h"

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
 
 u16  RXDATE  ;
 u16 CCR1_Val ;
 u16 CCR2_Val ; 
 u16 CCR3_Val ; 
 u16 CCR4_Val ; 
 
 extern u16 USART_RX_CNT;
 extern char  USART_RX_BUF[3] ;
 int return_true;
 extern true_flage;

int main(void)
{
  
	 CCR1_Val = 0;        
	 CCR2_Val = 0;
	 CCR3_Val = 0;
	 CCR4_Val = 0;
	/* TIM3 PWM波输出初始化，并使能TIM3 PWM输出 */
	TIM3_PWM_Init();
	
	NVIC_Configuration();
	
	USART1_Config();
	
	   CCR1_Val = 1000; 
	   CCR2_Val = 900;
	   CCR3_Val = 1000 ;
	   CCR4_Val = 1000;
	   TIM3_PWM_Init();
	
	      USART_RX_BUF[1] = 0 ;
        USART_RX_BUF[2]	= 0 ;

        USART_RX_CNT = 0;				
		while(1)
		{
	  
		  
//			if(USART_RX_BUF[2]>'9'||USART_RX_BUF[2]<'0')
//			{
//			  USART_RX_CNT = 0;
//			
//			}
			if((USART_RX_BUF[1]=='c'))
			{ 
				
				CCR1_Val = 1000; 
	      CCR2_Val = 1000;
	      CCR3_Val = 1000;
	      CCR4_Val = 1000;
				TIM3_PWM_Init();
				USART_SendData(USART1, 'c');
				USART_ClearFlag(USART1, USART_FLAG_RXNE);
				
				USART_RX_BUF[1] = 0 ;
        USART_RX_BUF[2]	= 0 ;	
				
				USART_RX_CNT = 0;
			}
			/*g  */
			if((USART_RX_BUF[1]=='r')&&(USART_RX_CNT==2))
			{
				return_true = atoi(&USART_RX_BUF[2]);
				CCR1_Val = 1000-return_true*100 ; 
				if(CCR1_Val<=590)
					CCR1_Val = 590;
				TIM3_PWM_Init();
				USART_SendData(USART1, 'r');
				USART_ClearFlag(USART1, USART_FLAG_RXNE);
				
				USART_RX_BUF[1] = 0 ;
        USART_RX_BUF[2]	= 0 ;

        USART_RX_CNT = 0;				
			}
			
			
		
			
			/*w  */
			if((USART_RX_BUF[1]=='b')&&(USART_RX_CNT==2))
			{
				return_true = atoi(&USART_RX_BUF[2]);
				CCR2_Val = 1000-return_true*200 ; 
				if(CCR1_Val<=400)
					CCR1_Val = 400;
				TIM3_PWM_Init();
				USART_SendData(USART1, 'b');
				USART_ClearFlag(USART1, USART_FLAG_RXNE);
				
				USART_RX_BUF[1] = 0 ;
        USART_RX_BUF[2]	= 0 ;
				
				USART_RX_CNT = 0;
			}
			
			
			 			
			//b
			if((USART_RX_BUF[1]=='w')&&(USART_RX_CNT==2))
			{
				return_true = atoi(&(USART_RX_BUF[2]));
				CCR3_Val = 1000-return_true*100 ;  
				if(CCR1_Val<=400)
					CCR1_Val = 400;
				TIM3_PWM_Init();
				USART_SendData(USART1, 'w');
				USART_ClearFlag(USART1, USART_FLAG_RXNE);
				
				USART_RX_BUF[1] = 0 ;
        USART_RX_BUF[2]	= 0 ;
				
				USART_RX_CNT = 0;
			}
			

			
			//r
			if((USART_RX_BUF[1]=='g')&&(USART_RX_CNT==2))
			{
				return_true = atoi(&USART_RX_BUF[2]);
				CCR4_Val = 1000-return_true*100 ; 
				if(CCR1_Val<=400)
									CCR1_Val = 400;				
				TIM3_PWM_Init();
				USART_SendData(USART1, 'g');
				USART_ClearFlag(USART1, USART_FLAG_RXNE);
				
				USART_RX_BUF[1] = 0 ;
        USART_RX_BUF[2]	= 0 ;
				
				USART_RX_CNT = 0;
			}
			

			
					
		
	  }
		
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
