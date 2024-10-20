#include "servo.hpp"

SERVO::SERVO(char out_servoID){
    servoID[0] = out_servoID;
    servo_init();
}

SERVO::~SERVO(){

}

/*******************************************************************************
****函数功能: 初始化舵机
****入口参数: 无
****出口参数: true: 设置成功 false: 设置失败
****函数备注: 无
********************************************************************************/

bool SERVO::servo_init(){
    init_uart2servo();

    char servoCommand[16];
    strcat(servoCommand, "#");                                                  //这三行拼凑出一个获取舵机ID的指令
    strcat(servoCommand, servoID);
    strcat(servoCommand, "PID!");

    ESP_ERROR_CHECK((UART_NUM_SERVO,servoCommand,strlen(servoCommand)));    //发送，然后读取串口
    unsigned int bufferLenth;
    char UARTdata[64];
    ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_SERVO, &bufferLenth));
    ESP_ERROR_CHECK(uart_read_bytes(UART_NUM_SERVO, UARTdata, bufferLenth, 100));
    ESP_ERROR_CHECK(uart_flush(UART_NUM_SERVO));

    char servoRetrun[8];                                                            
    strcat(servoRetrun, "#");                                                       //这三行拼凑出舵机“应该”有的返回值
    strcat(servoRetrun, servoID);
    strcat(servoRetrun, "!");

    char *isOK = NULL;                                                              //串口读到的信息里有“应该”有的返回值吗？
    isOK = strstr(UARTdata, servoRetrun);
    if(isOK != NULL){
        isOK = NULL;
        servoCommand[0] = {'\0'};
        strcat(servoCommand, "#");
        strcat(servoCommand, servoID);
        strcat(servoCommand, "PMOD!");

    }

}

bool SERVO::opendoor(){
    char send[7];
    uart_write_bytes(UART_NUM_SERVO, send , strlen(send));

}