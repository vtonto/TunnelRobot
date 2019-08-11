/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
//#include "bsp_usart.h"
#include "dma_uart.h"
#include <stdbool.h>

uint16_t Usart1_Rec_Cnt;
extern uint8_t DMA_Rece_Buf[DMA_Rec_Len];
//uint8_t Uart_Buffer[20];        //接收缓冲区
//uint8_t Uart_Rx = 0;             //Uart2_Buffer下标
//uint8_t Uart_head1;              //帧头1
//uint8_t Uart_head2;              //帧头2
//uint8_t Uart_Len;                //数据长度（第三字节以后包含crc）
//uint16_t Uart_temp;              //CRC16()返回值
//uint8_t Uart_Sta;                //数据帧正确标志
//uint8_t Uart_tx2;                //发送计数
//extern uint16_t ControVari[14];
extern bool  ReceiveComplete;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
// 串口中断服务函数
//void DEBUG_USART_IRQHandler(void)
//{
//  uint8_t ucTemp;
//	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
//	{		
//		ucTemp = USART_ReceiveData(DEBUG_USARTx);
//    USART_SendData(DEBUG_USARTx,ucTemp);     
//	}	 
//}

//void DEBUG_USART_IRQHandler() 
//{
//    printf("\r\n 进入中断 \r\n");	
//		if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET) 
//		{
//        printf("\r\n 进入中断if \r\n");			
//				USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//				Uart_Buffer[Uart_Rx] = USART_ReceiveData(USART1);
//        printf("\r\n 接收数据为 = 0x%02x \r\n",Uart_Buffer[Uart_Rx]);
//        printf("\r\n 接收下标为 = %d \r\n",Uart_Rx);			
//				Uart_Rx++; 
//				Uart_Rx &= 0xFF; 
//		}
//		if(Uart_Buffer[Uart_Rx-1] == 0xB5)   //判断帧头1
//		{
//			printf("\r\n 判断帧头1:接收下标为 = %d \r\n",Uart_Rx);	
//			Uart_head1 = Uart_Rx-1; 
//			printf("\r\n 接收到帧头1，其下标为%d  \r\n",Uart_head1);
//		}
//		else if((Uart_Rx-1 == Uart_head1+1)&&(Uart_Buffer[Uart_Rx-1] == 0x5B)) //判断帧头1数据后是否为帧头2
//		{
//			printf("\r\n 判断帧头2:接收下标为 = %d \r\n",Uart_Rx);	
//			Uart_head2 = Uart_Rx-1;
//			printf("\r\n 接收到帧头2，其下标为%d  \r\n",Uart_head2);
//		}
//		else if(Uart_Rx-1 == Uart_head2+1) //得到数据长度
//		{
//			printf("\r\n 得到数据长度:接收下标为 = %d \r\n",Uart_Rx);	
//			Uart_Len = Uart_Buffer [Uart_Rx-1]; 
//			printf("\r\n 接收到数据长度 =0x%02x  \r\n",Uart_Len);
//		}
//		else if(Uart_Rx-1 == Uart_head1 + Uart_Len+2) //确保接收一帧数据
//		{
//				Uart_temp = CRC16(&Uart_Buffer[Uart_head1],Uart_Len+1);  //计算crc
//				if(((Uart_temp&0x00ff)==Uart_Buffer[Uart_head1+Uart_Len+1])&&(((Uart_temp>>8)&0x00ff)==Uart_Buffer[Uart_head1+Uart_Len+2])) //判断crc是否正确
//				{
//					Uart_Sta = 1;  //标志置1
//					printf("\r\n 标志置1  \r\n");
//				}
////			Uart2_Sta = 1;
//			printf("\r\n 接收到一帧数据长度为 =0x%02x  \r\n",Uart_Len);
//		}
//			
//		if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET) 
//		{ 
//				USART_ClearFlag(USART1,USART_FLAG_ORE); 
//				USART_ReceiveData(USART1); 
//		} 

//		if(Uart_Sta) //检测到标志
//		{ 
//			  printf("\r\n 检测到标志\r\n");
//        for(Uart_tx2=Uart_head1+3; Uart_tx2 <= Uart_Len-2+3;Uart_tx2++)
//        {
//					ControVari[Uart_tx2-3] = Uart_Buffer[Uart_tx2];
//				}
//        ReceiveComplete = true;				
//				Uart_Rx = 0; //下标清0
//				Uart_Sta = 0; //标志置0
//		}
//}

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval None
  */
void DMA_USART_IRQHandler(void)                 //串口1中断服务程序
{
 
     if(USART_GetITStatus(DMA_USARTx, USART_IT_IDLE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
      {
          USART_ReceiveData(DMA_USARTx);//读取数据 注意：这句必须要，否则不能够清除中断标志位。
          Usart1_Rec_Cnt = DMA_Rec_Len-DMA_GetCurrDataCounter(DMA1_Channel5); //算出接本帧数据长度
         //***********帧数据处理函数************//
          //printf ("The lenght:%d\r\n",Usart1_Rec_Cnt);
          //printf ("The data:\r\n");
          //Usart_SendArray(DMA_USARTx, DMA_Rece_Buf, Usart1_Rec_Cnt);
          //printf ("\r\nOver! \r\n");
        //*************************************//
          USART_ClearITPendingBit(USART1, USART_IT_IDLE);         //清除中断标志
          DMA_Config();
				  ReceiveComplete = true;
     } 
 
} 
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
