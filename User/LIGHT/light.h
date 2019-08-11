#ifndef _LIGHT_H
#define _LIGHT_H

#include "stm32f10x.h"
#define  Light_EN_PORT    	                  GPIOC			              /* GPIO�˿� */
#define  Light_EN_CLK 	                      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  Light_EN_PIN		                      GPIO_Pin_8			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define  Light_DIR_PORT                       GPIOC			              /* GPIO�˿� */
#define  Light_DIR_CLK 	                      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  Light_DIR_PIN		                    GPIO_Pin_9			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// TIM5 ����Ƚ�ͨ��1   ����������PWM  PA0
#define            TIM4_CH2_GPIO_CLK             RCC_APB2Periph_GPIOB
#define            TIM4_CH2_PORT                 GPIOB
#define            TIM4_CH2_PIN                  GPIO_Pin_7

#define            LIGHT_TIM                     TIM4
#define            LIGHT_TIM_APBxClock_FUN       RCC_APB1PeriphClockCmd
#define            LIGHT_TIM_CLK                 RCC_APB1Periph_TIM4
#define            LIGHT_TIM_Period              (100-1)                     
#define            LIGHT_TIM_Prescaler           (72-1)

void General_Light_Config(void);
void LightPwnSet(uint16_t pwm);
#endif 
