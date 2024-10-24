/*******************************************************************************
****文件路径         : .\main\servo.cpp
****作者名称         : Scaxlibur
****文件版本         : V1.0.0
****创建日期         : 2024-10-21 19:47:26
****简要说明         : 开门舵机操作
********************************************************************************/

#include "servo.hpp"

SERVO::SERVO(char out_servoID[4] = "000")
{
    strcpy(servoID, out_servoID);
    servo_init();
}

SERVO::~SERVO()
{
    uart_driver_delete(UART_NUM_SERVO);
}

/*******************************************************************************
****函数功能: 初始化舵机
****入口参数: 无
****出口参数: true: 设置成功 false: 设置失败
****函数备注: 无
********************************************************************************/

bool SERVO::servo_init()
{
    init_uart2servo();
    strConnect(servoCommand, "#", servoID, "PID!");                                        // 获取舵机ID的指令
    ESP_ERROR_CHECK(uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand))); // 发送，然后读取串口
    char UARTdata[64];
    servoUARTread(UARTdata);
    strConnect(servoRetrun, "#", servoID, "!"); // 拼凑出舵机“应该”有的返回值
    char *isOK = NULL;                          // 串口读到的信息里有“应该”有的返回值吗？
    isOK = strstr(UARTdata, servoRetrun);
    if (isOK != NULL)
    {
        isOK = NULL;
        strcpy(UARTdata, "\0");
        strcpy(servoRetrun, "\0");
        strConnect(servoCommand, "#", servoID, "PMOD!"); // 舵机读取工作模式指令
        ESP_ERROR_CHECK(uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand)));
        servoUARTread(UARTdata);
        strConnect(servoRetrun, "#", servoID, "PMOD1!"); // 舵机的工作模式应该是舵机模式，顺时针最大270度，即1
        isOK = strstr(UARTdata, servoRetrun);
        if (isOK != NULL)
        {
            strcpy(UARTdata, "\0"); // 工作模式不是1就设置成1
            strConnect(servoCommand, "#", servoID, "PMOD1!");
            ESP_ERROR_CHECK(uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand)));
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

bool SERVO::opendoor()
{
    strConnect(servoCommand, "#", servoID, "P", openPos, "T1000!"); // #000P2000T1000!
    uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand));
    vTaskDelay(1000);
    strConnect(servoCommand, "#", servoID, "P", resetPos, "T1000!");
    uart_write_bytes(UART_NUM_SERVO, servoCommand, strlen(servoCommand));
}