#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f10x.h"
#include "gpio_config.h"

//***************************************************电机使能端口定义*********************************************************************//

/* 定义底盘左右两个电机的使能端口 EN DIR */
// 左边前方 EN
#define  LeftFront_EN_PORT    	  GPIOC			              /* GPIO端口 */
#define  LeftFront_EN_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define  LeftFront_EN_PIN		      GPIO_Pin_0			        /* 连接到SCL时钟线的GPIO */
// 左边前方 DIR
#define  LeftFront_DIR_PORT       GPIOC			              /* GPIO端口 */
#define  LeftFront_DIR_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define  LeftFront_DIR_PIN		    GPIO_Pin_1			        /* 连接到SCL时钟线的GPIO */

// 右边前方 EN
#define  RightFront_EN_PORT       GPIOC			              /* GPIO端口 */
#define  RightFront_EN_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define  RightFront_EN_PIN		    GPIO_Pin_2			        /* 连接到SCL时钟线的GPIO */
// 右边前方 DIR
#define  RightFront_DIR_PORT      GPIOC			              /* GPIO端口 */
#define  RightFront_DIR_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define  RightFront_DIR_PIN		    GPIO_Pin_3		          /* 连接到SCL时钟线的GPIO */

// 左边后方 EN
#define  LeftBack_EN_PORT    	    GPIOC			              /* GPIO端口 */
#define  LeftBack_EN_CLK 	        RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define  LeftBack_EN_PIN		      GPIO_Pin_4			        /* 连接到SCL时钟线的GPIO */
// 左边后方 DIR
#define  LeftBack_DIR_PORT        GPIOC			              /* GPIO端口 */
#define  LeftBack_DIR_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define  LeftBack_DIR_PIN		      GPIO_Pin_5			        /* 连接到SCL时钟线的GPIO */

// 右边后方 EN
#define  RightBack_EN_PORT        GPIOC			              /* GPIO端口 */
#define  RightBack_EN_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define  RightBack_EN_PIN		      GPIO_Pin_6			        /* 连接到SCL时钟线的GPIO */
// 右边后方 DIR
#define  RightBack_DIR_PORT       GPIOC			              /* GPIO端口 */
#define  RightBack_DIR_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define  RightBack_DIR_PIN		    GPIO_Pin_7		          /* 连接到SCL时钟线的GPIO */





//******************************************************电机定时器3定义********************************************************************//
/*                           ||||                                           ||||
              左前PA6(CH1)***********PA7(CH2)右前            左前PA4/5****************PA14/15右前
									*                        *									    *                        *
									*                        *								     	*                        *
									*                        *				    					*                        *
									*                        *								     	*                        *
									*                        *				     					*                        *
              左后PB0(CH3)***********PB1(CH4)右后			        左后PB0(CH3)***********PB1(CH4)右后							
*/
/************通用定时器TIM3参数定义，只限TIM2、3、4、5************/
// 我们这里默认使用TIM3   ARR = 100 -1   PSC = 72 -1     FERQUENCY = 72M / (72*100) = 10K Hz
// 电机工作频率为10K Hz 周期是 100us = 0.1ms
#define            MOTOR_TIM                   TIM3
#define            MOTOR_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            MOTOR_TIM_CLK               RCC_APB1Periph_TIM3
#define            MOTOR_TIM_Period            (100-1)                     
#define            MOTOR_TIM_Prescaler         (72-1)
//***********************************************************电机PWM口定义************************************************************//
/* 定义底盘左右两个电机的PWM输出端口 */
// TIM3 输出比较通道1   输出底盘左前电机PWM  PA6
#define            TIM3_CH1_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM3_CH1_PORT                 GPIOA
#define            TIM3_CH1_PIN                  GPIO_Pin_6

// TIM3 输出比较通道2   输出底盘右前电机PWM  PA7
#define            TIM3_CH2_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM3_CH2_PORT                 GPIOA
#define            TIM3_CH2_PIN                  GPIO_Pin_7

// TIM3 输出比较通道3   输出底盘左后电机PWM  PB0
#define            TIM3_CH3_GPIO_CLK             RCC_APB2Periph_GPIOB
#define            TIM3_CH3_PORT                 GPIOB
#define            TIM3_CH3_PIN                  GPIO_Pin_0


// TIM3 输出比较通道2   输出底盘右后电机PWM  PB1
#define            TIM3_CH4_GPIO_CLK             RCC_APB2Periph_GPIOB
#define            TIM3_CH4_PORT                 GPIOB
#define            TIM3_CH4_PIN                  GPIO_Pin_1

void General_Motor_Config(void);
void LeftFrontMotor(BitAction En, BitAction Dir, uint16_t pwm);
void RightFrontMotor(BitAction En, BitAction Dir, uint16_t pwm);
void LeftBackMotor(BitAction En, BitAction Dir, uint16_t pwm);
void RightBackMotor(BitAction En, BitAction Dir, uint16_t pwm);
#endif
