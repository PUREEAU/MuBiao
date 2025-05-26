#ifndef __TICK_H
#define __TICK_H

#include "stm32f1xx_hal.h"
#include "fashion_star_uart_servo.h"
#include "tim.h"

/**
  * @brief 定时器计时变量（extern 声明，实际定义在其他文件中）
  */
extern __IO uint32_t TickCnt;

/**
  * @brief 等待计时完成（阻塞式）
  * @details 启动定时器中断，并等待直到计时变量TickCnt变为0，然后停止定时器中断。
  */
void Tick_Wait(void);

/**
  * @brief 延时指定的微秒数
  * @param nTime 需要延时的微秒数
  * @details 将输入的微秒数转换为毫秒数，并设置计时变量TickCnt，然后调用Tick_Wait等待计时完成。
  */
void Tick_DelayUs(__IO uint32_t nTime);

/**
  * @brief 延时指定的毫秒数
  * @param nTime 需要延时的毫秒数
  * @details 直接设置计时变量TickCnt为目标毫秒数，然后调用Tick_Wait等待计时完成。
  */
void Tick_DelayMs(__IO uint32_t nTime);

/**
  * @brief 设置倒计时（非阻塞式）
  * @param nTime 倒计时的毫秒数
  * @details 设置计时变量TickCnt为指定的倒计时时间，并启动定时器中断。
  */
void Tick_CountdownBegin(__IO uint32_t nTime);

/**
  * @brief 撤销倒计时
  * @details 将计时变量TickCnt置为0，并停止定时器中断。
  */
void Tick_CountdownCancel(void);

/**
  * @brief 判断倒计时是否超时
  * @return 返回倒计时是否完成（0：未超时，1：已超时）
  * @details 检查计时变量TickCnt是否为0，如果是，则表示倒计时完成。
  */
uint8_t Tick_CountdownIsTimeout(void);

#endif // __TICK_H



