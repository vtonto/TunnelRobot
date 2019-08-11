#include "servo.h"

static void PLAT_PWM_GPIO_Config(void) 
{
		GPIO_InitTypeDef GPIO_InitStructure;	
	
		// TIM5 输出比较通道1 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM5_CH1_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM5_CH1_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM5_CH1_PORT, &GPIO_InitStructure);
		
		// TIM5 输出比较通道2 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM5_CH2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM5_CH2_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM5_CH2_PORT, &GPIO_InitStructure);
	
		// TIM5 输出比较通道3 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM5_CH3_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM5_CH3_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM5_CH3_PORT, &GPIO_InitStructure);
		
		// TIM5 输出比较通道4 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM5_CH4_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM5_CH4_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM5_CH4_PORT, &GPIO_InitStructure);
}

static void TIM5_Mode_Config(void)
{
  // 开启定时器时钟,即内部时钟CK_INT=72M
	SERVO_TIM_APBxClock_FUN(SERVO_TIM_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能定时器3时钟

/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为50K
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period = SERVO_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(SERVO_TIM, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OC1Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
	
	// 输出比较通道 2
	TIM_OC2Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
	
	// 输出比较通道 3
	//TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC3Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
	
//	// 输出比较通道 4
//	//TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC4Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);
	
	// 使能计数器
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


