#ifndef _DMA_UART_H
#define _DMA_UART_H

#include "stdio.h"
#include "sys.h"

#define DMA_Rec_Len 20

// 串口1-USART1
#define  DMA_USARTx                   USART1
#define  DMA_USART_CLK                RCC_APB2Periph_USART1
#define  DMA_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DMA_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DMA_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DMA_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DMA_USART_TX_GPIO_PORT       GPIOA   
#define  DMA_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DMA_USART_RX_GPIO_PORT       GPIOA
#define  DMA_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DMA_USART_IRQ                USART1_IRQn
#define  DMA_USART_IRQHandler         USART1_IRQHandler

// 串口对应的DMA请求通道
#define  USART_TX_DMA_CHANNEL         DMA1_Channel5

void DMA_UART_Config(void);
void DMA_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);


#endif //_DMA_UART_H
