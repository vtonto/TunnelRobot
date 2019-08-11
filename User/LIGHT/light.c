#include "light.h"

static void LIGHT_PWM_GPIO_Config(void) 
{
		GPIO_InitTypeDef GPIO_InitStructure;	
	
		// TIM4 ����Ƚ�ͨ��2 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM4_CH2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM4_CH2_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM4_CH2_PORT, &GPIO_InitStructure);
		
	  //GPIO_InitTypeDef GPIO_InitStructure;

		// ���ǰ�����EN GPIO��ʼ��
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
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
		LIGHT_TIM_APBxClock_FUN(LIGHT_TIM_CLK,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
		//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5 

	/*--------------------ʱ���ṹ���ʼ��-------------------------*/
		// �������ڣ���������Ϊ100K
		
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
		TIM_TimeBaseStructure.TIM_Period = LIGHT_TIM_Period;	
		// ����CNT��������ʱ�� = Fck_int/(psc+1)
		TIM_TimeBaseStructure.TIM_Prescaler= LIGHT_TIM_Prescaler;	
		// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// ����������ģʽ������Ϊ���ϼ���
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
		// �ظ���������ֵ��û�õ����ù�
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
		// ��ʼ����ʱ��
		TIM_TimeBaseInit(LIGHT_TIM, &TIM_TimeBaseStructure);

		/*--------------------����ȽϽṹ���ʼ��-------------------*/
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		// ����ΪPWMģʽ1
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		// ���ʹ��
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		// ���ͨ����ƽ��������	
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		
//		// ����Ƚ�ͨ�� 1
//		//TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
//		TIM_OC1Init(LIGHT_TIM, &TIM_OCInitStructure);
//		TIM_OC1PreloadConfig(LIGHT_TIM, TIM_OCPreload_Enable);
		
		// ����Ƚ�ͨ�� 2
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC2Init(LIGHT_TIM, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(LIGHT_TIM, TIM_OCPreload_Enable);
		
//		// ����Ƚ�ͨ�� 3
//		//TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
//		TIM_OC3Init(LIGHT_TIM, &TIM_OCInitStructure);
//		TIM_OC3PreloadConfig(LIGHT_TIM, TIM_OCPreload_Enable);
//		
//		// ����Ƚ�ͨ�� 4
//		//TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
//		TIM_OC4Init(LIGHT_TIM, &TIM_OCInitStructure);
//		TIM_OC4PreloadConfig(LIGHT_TIM, TIM_OCPreload_Enable);
//		
		// ʹ�ܼ�����
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
