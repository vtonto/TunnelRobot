#include "light.h"

static void LIGHT_PWM_GPIO_Config(void) 
{
		GPIO_InitTypeDef GPIO_InitStructure;	
	
		// TIM4 输出比较通道2 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM4_CH2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM4_CH2_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM4_CH2_PORT, &GPIO_InitStructure);
		
	  //GPIO_InitTypeDef GPIO_InitStructure;

		// 左边前方电机EN GPIO初始化
		RCC_APB2PeriphClockCmd(Light_EN_CLK, ENABLE);   
		GPIO_InitStructure.GPIO_Pin =  Light_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(Light_EN_PORT, &GPIO_InitStructure);	
		
		RCC_APB2PeriphClockCmd(Light_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  Light_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(Light_DIR_PORT, &GPIO_InitStructure);
}

static void TIM4_Mode_Config(void)
{
		// 开启定时器时钟,即内部时钟CK_INT=72M
		LIGHT_TIM_APBxClock_FUN(LIGHT_TIM_CLK,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
		//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5 

	/*--------------------时基结构体初始化-------------------------*/
		// 配置周期，这里配置为100K
		
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
		TIM_TimeBaseStructure.TIM_Period = LIGHT_TIM_Period;	
		// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
		TIM_TimeBaseStructure.TIM_Prescaler= LIGHT_TIM_Prescaler;	
		// 时钟分频因子 ，配置死区时间时需要用到
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// 计数器计数模式，设置为向上计数
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
		// 重复计数器的值，没用到不用管
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
		// 初始化定时器
		TIM_TimeBaseInit(LIGHT_TIM, &TIM_TimeBaseStructure);

		/*--------------------输出比较结构体初始化-------------------*/
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		// 配置为PWM模式1
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		// 输出使能
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		// 输出通道电平极性配置	
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		
//		// 输出比较通道 1
//		//TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
//		TIM_OC1Init(LIGHT_TIM, &TIM_OCInitStructure);
//		TIM_OC1PreloadConfig(LIGHT_TIM, TIM_OCPreload_Enable);
		
		// 输出比较通道 2
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC2Init(LIGHT_TIM, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(LIGHT_TIM, TIM_OCPreload_Enable);
		
//		// 输出比较通道 3
//		//TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
//		TIM_OC3Init(LIGHT_TIM, &TIM_OCInitStructure);
//		TIM_OC3PreloadConfig(LIGHT_TIM, TIM_OCPreload_Enable);
//		
//		// 输出比较通道 4
//		//TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
//		TIM_OC4Init(LIGHT_TIM, &TIM_OCInitStructure);
//		TIM_OC4PreloadConfig(LIGHT_TIM, TIM_OCPreload_Enable);
//		
		// 使能计数器
		TIM_Cmd(LIGHT_TIM, ENABLE);
}

void General_Light_Config(void)
{
		LIGHT_PWM_GPIO_Config();
		TIM4_Mode_Config();
}

void LightPwnSet(uint16_t pwm)
{
	GPIO_WriteBit(Light_EN_PORT, Light_EN_PIN, Bit_SET);
	GPIO_WriteBit(Light_DIR_PORT, Light_DIR_PIN, Bit_SET);
	TIM_SetCompare2(TIM4, pwm);
  //TIM_SetCompare4(TIM5, roll_pwm);
}
