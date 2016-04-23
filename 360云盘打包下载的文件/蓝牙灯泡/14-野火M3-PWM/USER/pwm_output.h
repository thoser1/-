#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H

#include "stm32f10x.h"

void TIM3_PWM_Init(void);
void TIM3_Mode_Config(void);
extern u16 CCR1_Val ;        
extern u16 CCR2_Val ;
extern u16 CCR3_Val ;
extern u16 CCR4_Val ;

#endif /* __PWM_OUTPUT_H */

