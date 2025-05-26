#include "Work.h"
#include "fashion_star_uart_servo.h"
#include "Tick.h"
#include "OLED.h"
//
uint8_t Mode = 9;

//
#define change_Angle 1.5
uint8_t Star_XorY = 0; // X:0  Y:1
float Add_X_coordinate = 0;
float Add_Y_coordinate = 0;
float curAngle_x = 0;
float curAngle_y = 0;
float Save_Star_Data_X[4]={0,0,0,0};
float Save_Star_Data_Y[4]={0,0,0,0};
uint8_t read_flag = 0;
float Back_central_x=0;
float Back_central_y=0;

//
uint8_t Mode3_Save_Data_flag = 0;

uint8_t Get_KeyData(void)
{
    uint8_t Key_Data = 0;
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) == GPIO_PIN_RESET)
    {
        HAL_Delay(25);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) == GPIO_PIN_RESET)
        Key_Data = 1;
    }
    else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8) == GPIO_PIN_RESET)
    {
        HAL_Delay(15);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8) == GPIO_PIN_RESET)
        Key_Data = 2;
    }
    else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9) == GPIO_PIN_RESET)
    {
        HAL_Delay(15);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9) == GPIO_PIN_RESET)
        Key_Data = 3;
    }
    else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) == GPIO_PIN_RESET)
    {
        HAL_Delay(15);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) == GPIO_PIN_RESET)
        Key_Data = 4;
    }
    else if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_RESET)
    {
        HAL_Delay(15);
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_RESET)
        Key_Data = 5;
    }
    else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET)
    {
        HAL_Delay(15);
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET)
        Key_Data = 6;
    }
    else 
        Key_Data = 0;
    return Key_Data;
}
void OLED_Work(void)
{
    if(Mode == 0 )
    {
        OLED_Printf(1, 1, OLED_6X8, "%2.2f", Save_Star_Data_X[0]);
        OLED_Printf(48, 1, OLED_6X8, "%2.2f", Save_Star_Data_Y[0]);
    
        OLED_Printf(1, 10, OLED_6X8, "%2.2f", Save_Star_Data_X[1]);
        OLED_Printf(48, 10, OLED_6X8, "%2.2f", Save_Star_Data_Y[1]);
    
        OLED_Printf(1, 20, OLED_6X8, "%2.2f", Save_Star_Data_X[2]);
        OLED_Printf(48, 20, OLED_6X8, "%2.2f", Save_Star_Data_Y[2]);
    
        OLED_Printf(1, 30, OLED_6X8, "%2.2f", Save_Star_Data_X[3]);
        OLED_Printf(48, 30, OLED_6X8, "%2.2f", Save_Star_Data_Y[3]);
        
        OLED_Printf(1, 40, OLED_6X8, "%2.2f", Add_X_coordinate);
        OLED_Printf(48, 40, OLED_6X8, "%2.2f", Add_Y_coordinate);
        OLED_Printf(96, 40, OLED_6X8, "%d", Star_XorY);
    }
    if(Mode == 1 )
    {
        OLED_Printf(1, 1, OLED_6X8, "%2.2f", Save_Star_Data_X[0]);
        OLED_Printf(48, 1, OLED_6X8, "%2.2f", Save_Star_Data_Y[0]);
    
        OLED_Printf(1, 10, OLED_6X8, "%2.2f", Save_Star_Data_X[1]);
        OLED_Printf(48, 10, OLED_6X8, "%2.2f", Save_Star_Data_Y[1]);
    
        OLED_Printf(1, 20, OLED_6X8, "%2.2f", Save_Star_Data_X[2]);
        OLED_Printf(48, 20, OLED_6X8, "%2.2f", Save_Star_Data_Y[2]);
    
        OLED_Printf(1, 30, OLED_6X8, "%2.2f", Save_Star_Data_X[3]);
        OLED_Printf(48, 30, OLED_6X8, "%2.2f", Save_Star_Data_Y[3]);
        
        OLED_Printf(1, 40, OLED_6X8, "%2.2f", Add_X_coordinate);
        OLED_Printf(48, 40, OLED_6X8, "%2.2f", Add_Y_coordinate);
        
        OLED_Printf(96, 40, OLED_6X8, "%d", Star_XorY);
        
        OLED_Printf(1, 50, OLED_6X8, "%d", Rx_1_Data);
    }
    
    OLED_Printf(90, 0, OLED_6X8, "Mode:%d", Mode);
    OLED_Update();
    Tick_DelayMs(5);
}
void Mode_Change_Work(void)
{
    if(Mode == 9) // 模式一下读取当前舵机角度
    {
        FSUS_QueryServoAngle(servoUsart,3,&Add_X_coordinate);
        Tick_DelayMs(5);
        FSUS_QueryServoAngle(servoUsart,0,&Add_Y_coordinate);
        Tick_DelayMs(5);
        Mode=3;
    }
    if(Get_KeyData() == 1)
    {
        Mode++;
        OLED_Clear();
        if(Mode == 4) Mode = 0;
    }
}


void Mode_1_Work(void)
{
    if(Mode == 0)
    {
        //修改想要定位的舵机
        if( Get_KeyData() == 2)
        {
            Star_XorY = !Star_XorY;
        }
        //修改舵机角度
        if( Get_KeyData() == 3 && Star_XorY == 0)
        {
            Add_X_coordinate += change_Angle;
            FSUS_SetServoAngle(servoUsart,3,Add_X_coordinate,200,100,0);
        }
        if( Get_KeyData() == 4 && Star_XorY == 0)
        {
            Add_X_coordinate -= change_Angle;
            FSUS_SetServoAngle(servoUsart,3,Add_X_coordinate,200,100,0);
        }
        if( Get_KeyData() == 3 && Star_XorY == 1)
        {
            Add_Y_coordinate += change_Angle;
            FSUS_SetServoAngle(servoUsart,0,Add_Y_coordinate,200,100,0);
        }
        if( Get_KeyData() == 4 && Star_XorY == 1)
        {
            Add_Y_coordinate -= change_Angle;
            FSUS_SetServoAngle(servoUsart,0,Add_Y_coordinate,200,100,0);
        }
        //保存舵机角度
        if( Get_KeyData() == 5 )
        {
            FSUS_QueryServoAngle(servoUsart,3,&curAngle_x);
            Tick_DelayMs(5);
            FSUS_QueryServoAngle(servoUsart,0,&curAngle_y);
            Tick_DelayMs(5);
            Save_Star_Data_X [read_flag]= curAngle_x;
            Save_Star_Data_Y [read_flag]= curAngle_y;
            read_flag++;
            if(read_flag>3)read_flag=0;
        }
        //模式1开始工作
        if( Get_KeyData() == 6 )
        {
            Back_central_x = ( (Save_Star_Data_X[0] + Save_Star_Data_X[2]) + (Save_Star_Data_X[1] + Save_Star_Data_X[3]) ) / 4;
            Back_central_y = ( (Save_Star_Data_Y[0] + Save_Star_Data_Y[2]) + (Save_Star_Data_Y[1] + Save_Star_Data_Y[3]) ) / 4;
            FSUS_SetServoAngle(servoUsart,3,Back_central_x,200,100,0);
            Tick_DelayMs(5);
            FSUS_SetServoAngle(servoUsart,0,Back_central_y,200,100,0);
            Tick_DelayMs(5);
        }
        
    }
}



void Arithmetic_Data(uint8_t start, uint8_t end) 
{
    // 确保start和end不越界（假设数组长度为N）
    // if (start >= N || end >= N) return;
    const int segments = 4; // 五等分，共5段
    for (int i = 0; i <= segments; i++) 
    { // 循环6次（0到5）
        float t = (float)i / (float)segments; // t范围0.0 ~ 1.0
        float X = Save_Star_Data_X[start] + t * (Save_Star_Data_X[end] - Save_Star_Data_X[start]);
        float Y = Save_Star_Data_Y[start] + t * (Save_Star_Data_Y[end] - Save_Star_Data_Y[start]);
        
        FSUS_SetServoAngle(servoUsart, 3, X, 200, 100, 0);
        FSUS_SetServoAngle(servoUsart, 0, Y, 200, 100, 0);
        
        // 根据实际舵机运动时间调整延时，或使用异步控制
        HAL_Delay(200);
    }
}

void Mode_2_Work(void)
{
    if(Mode == 1)
    {
        if( Get_KeyData() == 6 )
        {
            Arithmetic_Data(0,1);
            Arithmetic_Data(1,2);
            Arithmetic_Data(2,3);
            Arithmetic_Data(3,0);
            
            HAL_UART_Transmit(&huart1,(uint8_t *)"1",1,50);
        }
    }
}

void Mode_3_Work(void)
{
    if(Mode == 3)
    {
        if( Get_KeyData() == 5 && Mode3_Save_Data_flag == 0)
        {
            while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_RESET){;}
			Mode3_Save_Data_flag=1;
            HAL_UART_Transmit(&huart1,(uint8_t *)"2",1,50);
        }
        if( Get_KeyData() == 5 && Mode3_Save_Data_flag == 1)
        {
            Mode3_Save_Data_flag = 2;
            while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_RESET){;}
            HAL_UART_Transmit(&huart1,(uint8_t *)"0",1,50);
        }
        if( Get_KeyData() == 5 && Mode3_Save_Data_flag == 2)
        {
            Mode3_Save_Data_flag = 0;
            while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_RESET){;}
            HAL_UART_Transmit(&huart1,(uint8_t *)"3",1,50);
        }
        
        
    }
}

void All_Work(void)
{
    Mode_Change_Work();
    
    Mode_1_Work();
    Mode_2_Work();
    Mode_3_Work();
    OLED_Work();
    
}
