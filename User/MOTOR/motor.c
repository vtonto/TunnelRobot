#include "motor.h"

static void BASE_EN_DIR_PORT_Config(void) 
{
		GPIO_InitTypeDef GPIO_InitStructure;

		// ���ǰ�����EN GPIO��ʼ��
		RCC_APB2PeriphClockCmd(LeftFront_EN_CLK, ENABLE);   
		GPIO_InitStructure.GPIO_Pin =  LeftFront_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LeftFront_EN_PORT, &GPIO_InitStructure);	
		// ���ǰ�����DIR GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(LeftFront_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  LeftFront_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LeftFront_DIR_PORT, &GPIO_InitStructure);
		
		// �ұ�ǰ�����EN GPIO��ʼ��
		RCC_APB2PeriphClockCmd(RightFront_EN_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = RightFront_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RightFront_EN_PORT, &GPIO_InitStructure);		
		// �ұߵ��DIR GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(RightFront_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  RightFront_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RightFront_DIR_PORT, &GPIO_InitStructure);
		
		// ��ߺ󷽵��EN GPIO��ʼ��
		RCC_APB2PeriphClockCmd(LeftBack_EN_CLK, ENABLE);   
		GPIO_InitStructure.GPIO_Pin =  LeftBack_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LeftBack_EN_PORT, &GPIO_InitStructure);	
		// ��ߺ󷽵��DIR GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(LeftBack_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  LeftBack_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LeftBack_DIR_PORT, &GPIO_InitStructure);
		
		// �ұߺ󷽵��EN GPIO��ʼ��
		RCC_APB2PeriphClockCmd(RightBack_EN_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = RightBack_EN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RightBack_EN_PORT, &GPIO_InitStructure);
		
		// �ұߺ󷽵��DIR GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(RightBack_DIR_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  RightBack_DIR_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RightBack_DIR_PORT, &GPIO_InitStructure);
}

static void BASE_PWM_GPIO_Config(void) 
{
		GPIO_InitTypeDef GPIO_InitStructure;

		// TIM3����Ƚ�ͨ��1 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM3_CH1_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM3_CH1_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM3_CH1_PORT, &GPIO_InitStructure);
		
		// TIM3����Ƚ�ͨ��2 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM3_CH2_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE); //RCC_APB2PeriphClockCmd(TIM3_CH2_GPIO_CLK, ENABLE);//
		GPIO_InitStructure.GPIO_Pin =  TIM3_CH2_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_Init(TIM3_CH2_PORT, &GPIO_InitStructure);
	
		// TIM3����Ƚ�ͨ��3 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM3_CH3_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin =  TIM3_CH3_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TIM3_CH3_PORT, &GPIO_InitStructure);
		
		// TIM3����Ƚ�ͨ��4 GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TIM3_CH4_GPIO_CLK| RCC_APB2Periph_AFIO, ENABLE); //RCC_APB2PeriphClockCmd(TIM3_CH2_GPIO_CLK, ENABLE);//
		GPIO_InitStructure.GPIO_Pin =  TIM3_CH4_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_Init(TIM3_CH4_PORT, &GPIO_InitStructure);
		
}


/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

static void TIM3_Mode_Config(void)
{
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
		MOTOR_TIM_APBxClock_FUN(MOTOR_TIM_CLK,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
		//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5 

	/*--------------------ʱ���ṹ���ʼ��-------------------------*/
		// �������ڣ���������Ϊ100K
		
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
		TIM_TimeBaseStructure.TIM_Period = MOTOR_TIM_Period;	
		// ����CNT��������ʱ�� = Fck_int/(psc+1)
		TIM_TimeBaseStructure.TIM_Prescaler= MOTOR_TIM_Prescaler;	
		// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
		// ����������ģʽ������Ϊ���ϼ���
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
		// �ظ���������ֵ��û�õ����ù�
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
		// ��ʼ����ʱ��
		TIM_TimeBaseInit(MOTOR_TIM, &TIM_TimeBaseStructure);

		/*--------------------����ȽϽṹ���ʼ��-------------------*/
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		// ����ΪPWMģʽ1
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		// ���ʹ��
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		// ���ͨ����ƽ��������	
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		
		// ����Ƚ�ͨ�� 1
		//TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
		TIM_OC1Init(MOTOR_TIM, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);
		
		// ����Ƚ�ͨ�� 2
		//TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
		TIM_OC2Init(MOTOR_TIM, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);
		
		// ����Ƚ�ͨ�� 3
		//TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
		TIM_OC3Init(MOTOR_TIM, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);
		
		// ����Ƚ�ͨ�� 4
		//TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
		TIM_OC4Init(MOTOR_TIM, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(MOTOR_TIM, TIM_OCPreload_Enable);
		
		// ʹ�ܼ�����
		TIM_Cmd(MOTOR_TIM, ENABLE);
}

void General_Motor_Config(void)
{
		BASE_EN_DIR_PORT_Config();
		BASE_PWM_GPIO_Config();
		TIM3_Mode_Config();	
}
//*************************���̿���********************//
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
//*************************���̿���********************//

