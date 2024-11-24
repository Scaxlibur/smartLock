/*******************************************************************************
****文件路径         : .\main\servo.cpp
****作者名称         : Scaxlibur
****文件版本         : V1.0.0
****创建日期         : 2024-10-21 19:47:26
****简要说明         : 开门舵机操作
********************************************************************************/

#include "servo.hpp"

SERVO_class::SERVO_class(char out_servoID[4] = "000")
{
    strcpy(servoID, out_servoID);
    servo_init();
    printf("舵机对象构建");
}

SERVO_class::~SERVO_class()
{
    uart_driver_delete(UART_NUM_SERVO);
}

/*******************************************************************************
****函数功能: 初始化舵机
****入口参数: 无
****出口参数: true: 设置成功 false: 设置失败
****函数备注: 无
********************************************************************************/

bool SERVO_class::servo_init()
{
    init_uart2servo();      
    strcat(servoCommand, "#");// 获取舵机ID的指令
    strcat(servoCommand, servoID);
    strcat(servoCommand, "PID!");
    uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand)); // 发送，然后读取串口
    char UARTdata[64];
    servoUARTread(UARTdata);
    strcat(servoRetrun, "#");// 拼凑出舵机“应该”有的返回值
    strcat(servoRetrun, servoID);
    strcat(servoRetrun, "!");
    char *isOK = NULL;                          // 串口读到的信息里有“应该”有的返回值吗？
    isOK = strstr(UARTdata, servoRetrun);
    if (isOK != NULL)
    {
        isOK = NULL;
        strcpy(UARTdata, "\0");
        strcpy(servoRetrun, "\0");
        strcpy(servoCommand, "\0");
        strcat(servoCommand, "#");// 舵机读取工作模式指令
        strcat(servoCommand, servoID);
        strcat(servoCommand, "PMOD!");
        uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand));
        servoUARTread(UARTdata);
        strcat(servoRetrun, "#");// 舵机的工作模式应该是舵机模式，顺时针最大270度，即1
        strcat(servoRetrun, servoID);
        strcat(servoRetrun, "PMOD1!");
        isOK = strstr(UARTdata, servoRetrun);
        if (isOK != NULL)
        {
            strcpy(UARTdata, "\0"); // 工作模式不是1就设置成1
            strcpy(servoCommand, "\0");
            strcat(servoCommand, "#");
            strcat(servoCommand, servoID);
            strcat(servoCommand, "PMOD1!");
            uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand));
        }
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
****函数功能: 开门
****入口参数: 无
****出口参数: true: 开门成功 false: 开门失败
****函数备注: 初始位为500，开门位为2000
********************************************************************************/

bool SERVO_class::opendoor()
{
    strcpy(servoCommand, "/0");
    strcat(servoCommand, "#");// #000P2000T1000!
    strcat(servoCommand, servoID);
    strcat(servoCommand, "P");
    strcat(servoCommand, openPos);
    strcat(servoCommand, "T1000!");
    uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand));
    vTaskDelay(1000);

    strcpy(servoCommand, "/0");
    strcat(servoCommand, "#");
    strcat(servoCommand, servoID);
    strcat(servoCommand, "P");
    strcat(servoCommand, resetPos);
    strcat(servoCommand, "T1000!");
    uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand));
    return true;
}