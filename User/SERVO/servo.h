#ifndef _SERVO_H
#define _SERVO_H
#include "stm32f10x.h"


//*********************************************************�����ʱ��5����*****************************************************************//
/************ͨ�ö�ʱ��TIM5�������壬ֻ��TIM2��3��4��5************/
// ��������Ĭ��ʹ��TIM5   ARR = 200-1   PSC = 7200-1     FERQUENCY = 72M / (7200*200) = 50 Hz
// ȡ�������Ƶ��Ϊ50hz������Ϊ20ms   ARR       PSC   1~65536

#define            SERVO_TIM                   TIM5
#define            SERVO_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            SERVO_TIM_CLK               RCC_APB1Periph_TIM5
#define            SERVO_TIM_Period            (200-1)                     
#define            SERVO_TIM_Prescaler         (7200-1)
//************************************************************���pwm�ڶ���**************************************************************//
/* ������̨���������PWM����˿� */
// TIM5 ����Ƚ�ͨ��1   ����������PWM  PA0
#define            TIM5_CH1_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM5_CH1_PORT                 GPIOA
#define            TIM5_CH1_PIN                  GPIO_Pin_0

// TIM5 ����Ƚ�ͨ��2   ����������PWM  PA1
#define            TIM5_CH2_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM5_CH2_PORT                 GPIOA
#define            TIM5_CH2_PIN                  GPIO_Pin_1

// TIM5 ����Ƚ�ͨ��3   ����������PWM  PA0
#define            TIM5_CH3_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM5_CH3_PORT                 GPIOA
#define            TIM5_CH3_PIN                  GPIO_Pin_2

// TIM5 ����Ƚ�ͨ��2   ����������PWM  PA1
#define            TIM5_CH4_GPIO_CLK             RCC_APB2Periph_GPIOA
#define            TIM5_CH4_PORT                 GPIOA
#define            TIM5_CH4_PIN                  GPIO_Pin_3



//   500us �� 2500us ����1500usΪ��ֵ�������Ϊ90�ȡ�
//   2.5%     12.5%      7.5%      ���Զ�Ӧռ�ձ�
//   5        25         15        ���Զ�Ӧpulseֵ:����ARR=200   TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2)
//   ʵ�ʿ�������ֵΪ0~180��  pulse = uint16_t ((angle / 9) + 5)

void General_Servo_Config(void);
void PlatAngleSet(uint16_t pitch, int16_t roll);
void LightPwnSet(uint16_t pitch_pwm);
#endif
