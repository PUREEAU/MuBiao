/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "ring_buffer.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */


/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

typedef struct {
    UART_HandleTypeDef *pUSARTx;
    RingBufferTypeDef *sendBuf;
    RingBufferTypeDef  *recvBuf;
}Usart_DataTypeDef;
#define USART_RECV_BUF_SIZE 500
#define USART_SEND_BUF_SIZE 500
extern RingBufferTypeDef usart1SendRingBuf;
extern RingBufferTypeDef usart1RecvRingBuf;
extern Usart_DataTypeDef usart1;
extern Usart_DataTypeDef* servoUsart;
extern uint8_t usart1SendBuf[USART_SEND_BUF_SIZE+1];
extern uint8_t usart1RecvBuf[USART_RECV_BUF_SIZE+1];
void Usart_SendAll(Usart_DataTypeDef *usart);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

