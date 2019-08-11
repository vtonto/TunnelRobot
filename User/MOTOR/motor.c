#include "motor.h"

static void BASE_EN_DIR_PORT_Config(void) 
{
		GPIO_InitTypeDef GPIO_InitStructure;

		// 左边前方电机EN GPIO初始化
		RCC_APB2PeriphClockCmd(LeftFront_EN_CLK, ENABLE);   
		GPIO_InitStructure.GPIO_Pin =  LeftFront_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LeftFront_EN_PORT, &GPIO_InitStructure);	
		// 左边前方电机DIR GPIO 初始化
		RCC_APB2PeriphClockCmd(LeftFront_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  LeftFront_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LeftFront_DIR_PORT, &GPIO_InitStructure);
		
		// 右边前方电机EN GPIO初始化
		RCC_APB2PeriphClockCmd(RightFront_EN_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = RightFront_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RightFront_EN_PORT, &GPIO_InitStructure);		
		// 右边电机DIR GPIO 初始化
		RCC_APB2PeriphClockCmd(RightFront_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  RightFront_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RightFront_DIR_PORT, &GPIO_InitStructure);
		
		// 左边后方电机EN GPIO初始化
		RCC_APB2PeriphClockCmd(LeftBack_EN_CLK, ENABLE);   
		GPIO_InitStructure.GPIO_Pin =  LeftBack_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LeftBack_EN_PORT, &GPIO_InitStructure);	
		// 左边后方电机DIR GPIO 初始化
		RCC_APB2PeriphClockCmd(LeftBack_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  LeftBack_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LeftBack_DIR_PORT, &GPIO_InitStructure);
		
		// 右边后方电机EN GPIO初始化
		RCC_APB2PeriphClockCmd(RightBack_EN_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = RightBack_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RightBack_EN_PORT, &GPIO_InitStructure);
		
		// 右边后方电机DIR GPIO 初始化
		RCC_APB2PeriphClockCmd(RightBack_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  RightBack_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RightBack_DIR_PORT, &GPIO_InitStructure);
}

static void BASE_PWM_GPIO_Config(void) 
{
		GPIO_InitTypeDef GPIO_InitStructure;

		// TIM3输出比较通道1 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM3_CH1_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM3_CH1_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM3_CH1_PORT, &GPIO_InitStructure);
		
		// TIM3输出比较通道2 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM3_CH2_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE); //RCC_APB2PeriphClockCmd(TIM3_CH2_GPIO_CLK, ENABLE);//
		GPIO_InitStructure.GPIO_Pin =  TIM3_CH2_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_Init(TIM3_CH2_PORT, &GPIO_InitStructure);
	
		// TIM3输出比较通道3 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM3_CH3_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM3_CH3_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM3_CH3_PORT, &GPIO_InitStructure);
		
		// TIM3输出比较通道4 GPIO 初始化
		RCC_APB2PeriphClockCmd(TIM3_CH4_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE); //RCC_APB2PeriphClockCmd(TIM3_CH2_GPIO_CLK, ENABLE);//
		GPIO_InitStructure.GPIO_Pin =  TIM3_CH4_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_Init(TIM3_CH4_PORT, &GPIO_InitStructure);
		
}


/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)

static void TIM3_Mode_Config(void)
{
		// 开启定时器时钟,即内部时钟CK_INT=72M
		MOTOR_TIM_APBxClock_FUN(MOTOR_TIM_CLK,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
		//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5 

	/*--------------------时基结构体初始化-------------------------*/
		// 配置周期，这里配置为100K
		
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
		TIM_TimeBaseStructure.TIM_Period = MOTOR_TIM_Period;	
		// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
		TIM_TimeBaseStructure.TIM_Prescaler= MOTOR_TIM_Prescaler;	
		// 时钟分频因子 ，配置死区时间时需要用到
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// 计数器计数模式，设置为向上计数
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
		// 重复计数器的值，没用到不用管
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
		// 初始化定时器
		TIM_TimeBaseInit(MOTOR_TIM, &TIM_TimeBaseStructure);

		/*--------------------输出比较结构体初始化-------------------*/
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		// 配置为PWM模式1
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		// 输出使能
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		// 输出通道电平极性配置	
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		
		// 输出比较通道 1
		//TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
		TIM_OC1Init(MOTOR_TIM, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);
		
		// 输出比较通道 2
		//TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
		TIM_OC2Init(MOTOR_TIM, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);
		
		// 输出比较通道 3
		//TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
		TIM_OC3Init(MOTOR_TIM, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);
		
		// 输出比较通道 4
		//TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
		TIM_OC4Init(MOTOR_TIM, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);
		
		// 使能计数器
		TIM_Cmd(MOTOR_TIM, ENABLE);
}

void General_Motor_Config(void)
{
		BASE_EN_DIR_PORT_Config();
		BASE_PWM_GPIO_Config();
		TIM3_Mode_Config();	
}
//*************************底盘控制********************//
void LeftFrontMotor(BitAction En, BitAction Dir, uint16_t pwm)
{
	 GPIO_WriteBit(LeftFront_EN_PORT, LeftFront_EN_PIN, En);
   GPIO_WriteBit(LeftFront_DIR_PORT, LeftFront_DIR_PIN, Dir);
   TIM_SetCompare1(TIM3,pwm);
}	

void RightFrontMotor(BitAction En, BitAction Dir, uint16_t pwm)
{
	 GPIO_WriteBit(RightFront_EN_PORT, RightFront_EN_PIN, En);
   GPIO_WriteBit(RightFront_DIR_PORT, RightFront_DIR_PIN, Dir);
   TIM_SetCompare2(TIM3,pwm);
}	

void LeftBackMotor(BitAction En, BitAction Dir, uint16_t pwm)
{
	 GPIO_WriteBit(LeftBack_EN_PORT, LeftBack_EN_PIN, En);
   GPIO_WriteBit(LeftBack_DIR_PORT, LeftBack_DIR_PIN, Dir);
   TIM_SetCompare3(TIM3,pwm);
}	

void RightBackMotor(BitAction En, BitAction Dir, uint16_t pwm)
{
	 GPIO_WriteBit(RightBack_EN_PORT, RightBack_EN_PIN, En);
   GPIO_WriteBit(RightBack_DIR_PORT, RightBack_DIR_PIN, Dir);
   TIM_SetCompare4(TIM3,pwm);
}	
//*************************底盘控制********************//

