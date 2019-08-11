#include "main.h"

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

int main(void)
{
	unsigned char chrTemp[30];
	//unsigned char str[100];
	float a[3],w[3],h[3],Angle[3];
	
	delay_init();
	//ADCx_Init();
	IIC_Init();
	General_Motor_Config();
	General_Servo_Config();
	DMA_UART_Config();
	General_Light_Config();
	
	PlatAngleSet(15, 16);
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
	
//**********************************************************************//
//	while(1)
//	{
//		if(ReceiveComplete)
//		{
//			if(DMA_Rece_Buf[0]==127 && DMA_Rece_Buf[1]==127)
//			{
//			  printf("uart debug start\n");
//				ReceiveComplete = false;
//			  break;
//			}
//		}
//	}
//**********************************************************************//
	
	while(1)
	{
		delay_ms(100);
		IICreadBytes(0x50, AX, 24,&chrTemp[0]);
		a[0] = (float)CharToShort(&chrTemp[0])/32768*16;
		a[1] = (float)CharToShort(&chrTemp[2])/32768*16;
		a[2] = (float)CharToShort(&chrTemp[4])/32768*16;
		w[0] = (float)CharToShort(&chrTemp[6])/32768*2000;
		w[1] = (float)CharToShort(&chrTemp[8])/32768*2000;
		w[2] = (float)CharToShort(&chrTemp[10])/32768*2000;
		h[0] = CharToShort(&chrTemp[12]);
		h[1] = CharToShort(&chrTemp[14]);
		h[2] = CharToShort(&chrTemp[16]);
		Angle[0] = (float)CharToShort(&chrTemp[18])/32768*180;
		Angle[1] = (float)CharToShort(&chrTemp[20])/32768*180;
		Angle[2] = (float)CharToShort(&chrTemp[22])/32768*180;
		
		printf("0x50:  a:%.3f %.3f %.3f w:%.3f %.3f %.3f  h:%.0f %.0f %.0f  Angle:%.3f %.3f %.3f \r\n",a[0],a[1],a[2],w[0],w[1],w[2],h[0],h[1],h[2],Angle[0],Angle[1],Angle[2]);
		
		
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
