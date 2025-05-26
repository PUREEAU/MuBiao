#include "Tick.h"

// 定时器计时变量
__IO uint32_t TickCnt;

/**
  * @brief 等待计时完成（阻塞式）
  * @details 启动定时器中断，并等待直到计时变量TickCnt变为0，然后停止定时器中断。
  */
void Tick_Wait() {
    // 启动定时器中断
    HAL_TIM_Base_Start_IT(&htim2);
    
    // 阻塞等待，直到计时完成（TickCnt变为0）
    while (TickCnt > 0);
    
    // 停止定时器中断
    HAL_TIM_Base_Stop_IT(&htim2);
}

/**
  * @brief 延时指定的微秒数
  * @param nTime 需要延时的微秒数
  * @details 将输入的微秒数转换为毫秒数，并设置计时变量TickCnt，然后调用Tick_Wait等待计时完成。
  */
void Tick_DelayUs(__IO uint32_t nTime) {
    // 将微秒转换为毫秒
    uint32_t nTime_us = nTime / 1000;
    
    // 设置计时变量
    TickCnt = nTime_us;
    
    // 等待计时完成
    Tick_Wait();
}

/**
  * @brief 延时指定的毫秒数
  * @param nTime 需要延时的毫秒数
  * @details 直接设置计时变量TickCnt为目标毫秒数，然后调用Tick_Wait等待计时完成。
  */
void Tick_DelayMs(__IO uint32_t nTime) {
    // 设置计时变量
    TickCnt = nTime;
    
    // 等待计时完成
    Tick_Wait();
}

/**
  * @brief 设置倒计时（非阻塞式）
  * @param nTime 倒计时的毫秒数
  * @details 设置计时变量TickCnt为指定的倒计时时间，并启动定时器中断。
  */
void Tick_CountdownBegin(__IO uint32_t nTime) {
    // 设置计时变量
    TickCnt = nTime;
    
    // 启动定时器中断
    HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief 撤销倒计时
  * @details 将计时变量TickCnt置为0，并停止定时器中断。
  */
void Tick_CountdownCancel(void) {
    // 将计时变量置为0
    TickCnt = 0;
    
    // 停止定时器中断
    HAL_TIM_Base_Stop_IT(&htim2);
}

/**
  * @brief 判断倒计时是否超时
  * @return 返回倒计时是否完成（0：未超时，1：已超时）
  * @details 检查计时变量TickCnt是否为0，如果是，则表示倒计时完成。
  */
uint8_t Tick_CountdownIsTimeout(void) {
    // 如果计时变量为0，表示倒计时完成
    return TickCnt == 0;
}

