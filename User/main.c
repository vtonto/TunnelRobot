#include "main.h"

/**
  * @problem  ���������ڶ���ͨ���޷����Ƶ��ת
  * @date  7/19/2019  
  * @solution pwm1 + en2 + dir2  �����ת (en dir������)
	  @solution pwm2 + en1 + dir1  ���ת�� (ȷ��pwm2�˿�û������)
		@solution pwm2 + en1 + dir2  ���ת�� (ȷ��dir2�˿�û������)
		@solution pwm2 + en2 + dir2  �����ת (ȷ��dir2�˿�û������)
		@solution pwm2 + en2(PB4) + dir2  ���ת��������
  */
	
/**
  * @problem  ���������ڶ���ͨ���޷����Ƶ������
  * @date  7/19/2019  
  * @solution pwm2 + en2 + dir2  �ӵ���������һ��ͨ���������ת���ų���������������
  * @solution pwm2 + en2 + dir1  �����ת��
  */
	
/**
  * @problem  �������޷���pwm���ƣ�һ���Ͼ�������ʹ�����ź�ͨ��
  * @date  7/14/2019 
  * @solution ��
  */
int x,y,z;
bool strightFlag = false;
bool first_in = true;
int ini_angle,cur_angle;
int main(void)
{
	//char str[100];
	//unsigned char len,i;
	
	delay_init();
	ADCx_Init();
	General_Motor_Config();
	General_Servo_Config();
	DMA_UART_Config();
	General_Light_Config();
	
	Initial_UART4(9600);
	delay_ms(1000);//�ȵ�JY-91��ʼ�����
	
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
	
//********************************************************************//
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
//********************************************************************//
	while(1)
	{
//		//printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
		x = (float)stcAngle.Angle[0]/32768*180;
		y = (float)stcAngle.Angle[1]/32768*180;
		z = (float)stcAngle.Angle[2]/32768*180;
		printf("angle-x:%d,angle-y:%d,angle-z:%d\r\n",x,y,z);
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
		}
    //bool strightFlag = false;
    //bool first_in = true;		
		if(!strightFlag && leftFront_pwm==rightFront_pwm)
		{
			 first_in = true;
		}
		strightFlag = false;
		if(leftFront_pwm==rightFront_pwm)
		{
			strightFlag = true;
		}
		
		if(strightFlag && first_in)
		{
			ini_angle = (float)stcAngle.Angle[2]/32768*180;
			first_in = false;
		}
		
		cur_angle = (float)stcAngle.Angle[2]/32768*180;	
    if(strightFlag)		
		{
			if(cur_angle<ini_angle){
				leftFront_pwm --;
				leftBack_pwm --;
			}
			else{
				rightFront_pwm--;
				rightBack_pwm--;
	    }
		}
		
		LeftFrontMotor(leftFront_EN, leftFront_DIR, leftFront_pwm);
		RightFrontMotor(rightFront_EN, rightFront_DIR, rightFront_pwm);
    LeftBackMotor(leftBack_EN, leftBack_DIR, leftBack_pwm);
    RightBackMotor(rightBack_EN, rightBack_DIR, rightBack_pwm);
		PlatAngleSet(pitch_angle, roll_angle);
		LightPwnSet(light_pwm);
	}
}
