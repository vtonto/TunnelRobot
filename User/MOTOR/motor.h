#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f10x.h"
#include "gpio_config.h"

//***************************************************���ʹ�ܶ˿ڶ���*********************************************************************//

/* ��������������������ʹ�ܶ˿� EN DIR */
// ���ǰ�� EN
#define  LeftFront_EN_PORT    	  GPIOC			              /* GPIO�˿� */
#define  LeftFront_EN_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  LeftFront_EN_PIN		      GPIO_Pin_0			        /* ���ӵ�SCLʱ���ߵ�GPIO */
// ���ǰ�� DIR
#define  LeftFront_DIR_PORT       GPIOC			              /* GPIO�˿� */
#define  LeftFront_DIR_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  LeftFront_DIR_PIN		    GPIO_Pin_1			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// �ұ�ǰ�� EN
#define  RightFront_EN_PORT       GPIOC			              /* GPIO�˿� */
#define  RightFront_EN_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  RightFront_EN_PIN		    GPIO_Pin_2			        /* ���ӵ�SCLʱ���ߵ�GPIO */
// �ұ�ǰ�� DIR
#define  RightFront_DIR_PORT      GPIOC			              /* GPIO�˿� */
#define  RightFront_DIR_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  RightFront_DIR_PIN		    GPIO_Pin_3		          /* ���ӵ�SCLʱ���ߵ�GPIO */

// ��ߺ� EN
#define  LeftBack_EN_PORT    	    GPIOC			              /* GPIO�˿� */
#define  LeftBack_EN_CLK 	        RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  LeftBack_EN_PIN		      GPIO_Pin_4			        /* ���ӵ�SCLʱ���ߵ�GPIO */
// ��ߺ� DIR
#define  LeftBack_DIR_PORT        GPIOC			              /* GPIO�˿� */
#define  LeftBack_DIR_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  LeftBack_DIR_PIN		      GPIO_Pin_5			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// �ұߺ� EN
#define  RightBack_EN_PORT        GPIOC			              /* GPIO�˿� */
#define  RightBack_EN_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  RightBack_EN_PIN		      GPIO_Pin_6			        /* ���ӵ�SCLʱ���ߵ�GPIO */
// �ұߺ� DIR
#define  RightBack_DIR_PORT       GPIOC			              /* GPIO�˿� */
#define  RightBack_DIR_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define  RightBack_DIR_PIN		    GPIO_Pin_7		          /* ���ӵ�SCLʱ���ߵ�GPIO */





//******************************************************�����ʱ��3����********************************************************************//
/*                           ||||                                           ||||
              ��ǰPA6(CH1)***********PA7(CH2)��ǰ            ��ǰPA4/5****************PA14/15��ǰ
									*                        *									    *                        *
									*                        *								     	*                        *
									*                        *				    					*                        *
									*                        *								     	*                        *
									*                        *				     					*                        *
              ���PB0(CH3)***********PB1(CH4)�Һ�			        ���PB0(CH3)***********PB1(CH4)�Һ�							
*/
/************ͨ�ö�ʱ��TIM3�������壬ֻ��TIM2��3��4��5************/
// ��������Ĭ��ʹ��TIM3   ARR = 100 -1   PSC = 72 -1     FERQUENCY = 72M / (72*100) = 10K Hz
// �������Ƶ��Ϊ10K Hz ������ 100us = 0.1ms
#define            MOTOR_TIM                   TIM3
#define            MOTOR_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            MOTOR_TIM_CLK               RCC_APB1Periph_TIM3
#define            MOTOR_TIM_Period            (100-1)                     
#define            MOTOR_TIM_Prescaler         (72-1)
//***********************************************************���PWM�ڶ���************************************************************//
/* ��������������������PWM����˿� */
// TIM3 ����Ƚ�ͨ��1   ���������ǰ���PWM  PA6
#define            TIM3_CH1_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM3_CH1_PORT                 GPIOA
#define            TIM3_CH1_PIN                  GPIO_Pin_6

// TIM3 ����Ƚ�ͨ��2   ���������ǰ���PWM  PA7
#define            TIM3_CH2_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM3_CH2_PORT                 GPIOA
#define            TIM3_CH2_PIN                  GPIO_Pin_7

// TIM3 ����Ƚ�ͨ��3   ������������PWM  PB0
#define            TIM3_CH3_GPIO_CLK             RCC_APB2Periph_GPIOB
#define            TIM3_CH3_PORT                 GPIOB
#define            TIM3_CH3_PIN                  GPIO_Pin_0


// TIM3 ����Ƚ�ͨ��2   ��������Һ���PWM  PB1
#define            TIM3_CH4_GPIO_CLK             RCC_APB2Periph_GPIOB
#define            TIM3_CH4_PORT                 GPIOB
#define            TIM3_CH4_PIN                  GPIO_Pin_1

void General_Motor_Config(void);
void LeftFrontMotor(BitAction En, BitAction Dir, uint16_t pwm);
void RightFrontMotor(BitAction En, BitAction Dir, uint16_t pwm);
void LeftBackMotor(BitAction En, BitAction Dir, uint16_t pwm);
void RightBackMotor(BitAction En, BitAction Dir, uint16_t pwm);
#endif
