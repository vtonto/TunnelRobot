#ifndef _SERVO_H
#define _SERVO_H
#include "stm32f10x.h"


//*********************************************************舵机定时器5定义*****************************************************************//
/************通用定时器TIM5参数定义，只限TIM2、3、4、5************/
// 我们这里默认使用TIM5   ARR = 200-1   PSC = 7200-1     FERQUENCY = 72M / (7200*200) = 50 Hz
// 取舵机工作频率为50hz，周期为20ms   ARR       PSC   1~65536

#define            SERVO_TIM                   TIM5
#define            SERVO_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            SERVO_TIM_CLK               RCC_APB1Periph_TIM5
#define            SERVO_TIM_Period            (200-1)                     
#define            SERVO_TIM_Prescaler         (7200-1)
//************************************************************舵机pwm口定义**************************************************************//
/* 定义云台两个舵机的PWM输出端口 */
// TIM5 输出比较通道1   输出翻滚舵机PWM  PA0
#define            TIM5_CH1_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM5_CH1_PORT                 GPIOA
#define            TIM5_CH1_PIN                  GPIO_Pin_0

// TIM5 输出比较通道2   输出俯仰舵机PWM  PA1
#define            TIM5_CH2_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM5_CH2_PORT                 GPIOA
#define            TIM5_CH2_PIN                  GPIO_Pin_1

// TIM5 输出比较通道3   输出翻滚舵机PWM  PA0
#define            TIM5_CH3_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM5_CH3_PORT                 GPIOA
#define            TIM5_CH3_PIN                  GPIO_Pin_2

// TIM5 输出比较通道2   输出俯仰舵机PWM  PA1
#define            TIM5_CH4_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM5_CH4_PORT                 GPIOA
#define            TIM5_CH4_PIN                  GPIO_Pin_3



//   500us 到 2500us 其中1500us为中值，即舵机为90度。
//   2.5%     12.5%      7.5%      各自对应占空比
//   5        25         15        各自对应pulse值:对于ARR=200   TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2)
//   实际控制输入值为0~180°  pulse = uint16_t ((angle / 9) + 5)

void General_Servo_Config(void);
void PlatAngleSet(uint16_t pitch, int16_t roll);
void LightPwnSet(uint16_t pitch_pwm);
#endif
