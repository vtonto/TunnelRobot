#include "stm32f10x.h"
#include "motor.h"
#include "delay.h"
#include "sys.h"
#include "bsp_adc.h"
#include "motor.h"
#include "servo.h"
//#include "bsp_usart.h"
#include "dma_uart.h"
#include "light.h"
#include <stdbool.h>

//#include "IOI2C.h"
//#include "REG.h"
//********************************控制变量定义***********************************//
//4个字节
uint8_t   pitch_angle =15;
uint8_t   roll_angle  =15;
//3个字节
BitAction  leftFront_EN;
BitAction  leftFront_DIR;
uint8_t    leftFront_pwm;
//3个字节
BitAction  rightFront_EN;
BitAction  rightFront_DIR;
uint8_t    rightFront_pwm;

BitAction  leftBack_EN;
BitAction  leftBack_DIR;
uint8_t    leftBack_pwm;

BitAction  rightBack_EN;
BitAction  rightBack_DIR;
uint8_t    rightBack_pwm;
//4个字节

uint8_t    light_pwm;

#define ON   Bit_SET
#define OFF  Bit_RESET 

#define FORW Bit_SET
#define BACK Bit_RESET

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];	 
uint32_t ADC_ConvertedValueLocal[NOFCHANEL]; 
extern uint8_t DMA_Rece_Buf[DMA_Rec_Len];
bool  ReceiveComplete = false;



/**
  * @problem  电机驱动板第二个通道无法控制电机转
  * @date  7/19/2019  
  * @solution pwm1 + en2 + dir2  电机不转 (en dir有问题)
	  @solution pwm2 + en1 + dir1  电机转动 (确认pwm2端口没有问题)
		@solution pwm2 + en1 + dir2  电机转动 (确认dir2端口没有问题)
		@solution pwm2 + en2 + dir2  电机不转 (确认dir2端口没有问题)
		@solution pwm2 + en2(PB4) + dir2  电机转，问题解决
  */
	
/**
  * @problem  电机驱动板第二个通道无法控制电机方向
  * @date  7/19/2019  
  * @solution pwm2 + en2 + dir2  接电机驱动板第一个通道，电机不转，排除电机驱动板的问题
  * @solution pwm2 + en2 + dir1  电机不转向
  */
	
/**
  * @problem  照明灯无法用pwm控制，一接上就两，即使不接信号通道
  * @date  7/14/2019 
  * @solution 无
  */
	
void ShortToChar(short sData,unsigned char cData[]);
short CharToShort(unsigned char cData[]);

int main(void)
{
	delay_init();
	ADCx_Init();
	General_Motor_Config();
	General_Servo_Config();
	DMA_UART_Config();
	General_Light_Config();
	PlatAngleSet(15, 16);
	//*******************************************************************//
  //PlatAngleSet(15, 15);

	LightPwnSet(0);
	LeftFrontMotor(ON, BACK, 0);    // 1
	RightFrontMotor(ON, FORW, 0);    // 2
	LeftBackMotor(ON, BACK, 0);    // 3
	RightBackMotor(ON, FORW, 0);    // 4	
	
//
	
	//*******************************************************************//
	for(int i=0;i<16;i++)
	{
		DMA_Rece_Buf[i]=0;
	}
	
	while(1)
	{
		if(ReceiveComplete)
		{
			if(DMA_Rece_Buf[0]==127 && DMA_Rece_Buf[1]==127)
			{
			  printf("uart debug start\n");
				ReceiveComplete = false;
			  break;
			}
		}
	}
	while(1)
	{
		if(ReceiveComplete)
		{
			printf("fill in data\n");
			leftFront_EN      = (BitAction)DMA_Rece_Buf[0];
      leftFront_DIR     = (BitAction)DMA_Rece_Buf[1];
      leftFront_pwm     = DMA_Rece_Buf[2];
			rightFront_EN     = (BitAction)DMA_Rece_Buf[3];
      rightFront_DIR    = (BitAction)DMA_Rece_Buf[4];   
      rightFront_pwm    = DMA_Rece_Buf[5];
			leftBack_EN       = (BitAction)DMA_Rece_Buf[6];
      leftBack_DIR      = (BitAction)DMA_Rece_Buf[7];
      leftBack_pwm      = DMA_Rece_Buf[8];
			rightBack_EN      = (BitAction)DMA_Rece_Buf[9];
      rightBack_DIR     = (BitAction)DMA_Rece_Buf[10];   
      rightBack_pwm     = DMA_Rece_Buf[11];
			pitch_angle       = DMA_Rece_Buf[12]; 
		  roll_angle        = DMA_Rece_Buf[13];
      light_pwm         = DMA_Rece_Buf[14];			
			ReceiveComplete = false;
			printf("leftFront_EN value = %d \n",leftFront_EN);
			printf("leftFront_DIR value = %d \n",leftFront_DIR);
			printf("leftFront_pwm value = %d \n",leftFront_pwm);
			printf("rightFront_EN value = %d \n",rightFront_EN);
			printf("rightFront_DIR value = %d \n",rightFront_DIR);
			printf("rightFront_pwm value = %d \n",rightFront_pwm);
		  printf("leftBack_EN value = %d \n",leftBack_EN);
			printf("leftBack_DIR value = %d \n",leftBack_DIR);
			printf("leftBack_pwm value = %d \n",leftBack_pwm);
			printf("rightBack_EN value = %d \n",rightBack_EN);
			printf("rightBack_DIR value = %d \n",rightBack_DIR);
			printf("rightBack_pwm value = %d \n",rightBack_pwm);
			printf("pitch_angle value = %d \n",pitch_angle);			
			printf("roll_angle value = %d \n",roll_angle);		
			printf("light_pwm value = %d \n",light_pwm);			
		}
		LeftFrontMotor(leftFront_EN, leftFront_DIR, leftFront_pwm);
		RightFrontMotor(rightFront_EN, rightFront_DIR, rightFront_pwm);
    LeftBackMotor(leftBack_EN, leftBack_DIR, leftBack_pwm);
    RightBackMotor(rightBack_EN, rightBack_DIR, rightBack_pwm);
		PlatAngleSet(pitch_angle, roll_angle);
		LightPwnSet(light_pwm);
	}
}
/*********************************************END OF FILE**********************/
// char 1 byte      short 2 bytes
void ShortToChar(short sData,unsigned char cData[])
{
	cData[0]=sData&0xff;
	cData[1]=sData>>8;
}
short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}