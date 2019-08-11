#include "servo.h"

static void PLAT_PWM_GPIO_Config(void) 
{
		GPIO_InitTypeDef GPIO_InitStructure;	
	
		// TIM5 ����Ƚ�ͨ��1 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM5_CH1_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM5_CH1_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM5_CH1_PORT, &GPIO_InitStructure);
		
		// TIM5 ����Ƚ�ͨ��2 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM5_CH2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM5_CH2_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM5_CH2_PORT, &GPIO_InitStructure);
	
		// TIM5 ����Ƚ�ͨ��3 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM5_CH3_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM5_CH3_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM5_CH3_PORT, &GPIO_InitStructure);
		
		// TIM5 ����Ƚ�ͨ��4 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM5_CH4_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM5_CH4_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM5_CH4_PORT, &GPIO_InitStructure);
}

static void TIM5_Mode_Config(void)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	SERVO_TIM_APBxClock_FUN(SERVO_TIM_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ50K
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period = SERVO_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(SERVO_TIM, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OC1Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 2
	TIM_OC2Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 3
	//TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC3Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
	
//	// ����Ƚ�ͨ�� 4
//	//TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC4Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(SERVO_TIM, ENABLE);
}

void General_Servo_Config(void)
{
	PLAT_PWM_GPIO_Config();
	TIM5_Mode_Config();
}

void PlatAngleSet(uint16_t pitch_pwm, int16_t roll_pwm)
{
	TIM_SetCompare1(TIM5, pitch_pwm);
  TIM_SetCompare2(TIM5, roll_pwm);
}


