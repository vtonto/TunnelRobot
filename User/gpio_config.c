#include "gpio_config.h"




void GENERAL_TIM_Init(void)
{
	BASE_EN_DIR_PORT_Config();
	BASE_PWM_GPIO_Config();		
	PLAT_PWM_GPIO_Config();
	TIM3_Mode_Config();
	TIM4_Mode_Config();
}


