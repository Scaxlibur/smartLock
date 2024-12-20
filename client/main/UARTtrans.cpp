#include "UARTtrans.hpp"

static const int RX_BUF_SIZE = 1024;  //串口接收缓冲区大小

const uart_config_t uart2id_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT
};

const uart_config_t uart2screen_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT
};

const uart_config_t uart2servo_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT
};

const uart_config_t uart2su03t_config = {
    .baud_rate = 9600,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT
};

void init_uart2id(void)            //配置连接到指纹识别器的UART
{
    if(uart_is_driver_installed(UART_NUM_ID) == false){//注册驱动前检查，避免重复注册报错
        ESP_ERROR_CHECK(uart_param_config(UART_NUM_ID, &uart2id_config));
        ESP_ERROR_CHECK(uart_set_pin(UART_NUM_ID, UART_NUM_ID_TX, UART_NUM_ID_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
        ESP_ERROR_CHECK(uart_driver_install(UART_NUM_ID, RX_BUF_SIZE * 2, 0, 0, NULL, 0));
    };
}

void init_uart2screen(void)         //配置连接到串口屏的UART
{
    if(uart_is_driver_installed(UART_NUM_SCREEN) == false){
        ESP_ERROR_CHECK(uart_param_config(UART_NUM_SCREEN, &uart2screen_config));
        ESP_ERROR_CHECK(uart_set_pin(UART_NUM_SCREEN, UART_NUM_SCREEN_TX, UART_NUM_SCREEN_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
        ESP_ERROR_CHECK(uart_driver_install(UART_NUM_SCREEN, RX_BUF_SIZE * 2, 0, 0, NULL, 0));
    };
}

void init_uart2servo(void)         //配置连接到舵机的UART
{
    if(uart_is_driver_installed(UART_NUM_SERVO) == false){
        ESP_ERROR_CHECK(uart_param_config(UART_NUM_SERVO, &uart2servo_config));
        ESP_ERROR_CHECK(uart_set_pin(UART_NUM_SERVO, UART_NUM_SERVO_TX, UART_NUM_SERVO_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
        ESP_ERROR_CHECK(uart_driver_install(UART_NUM_SERVO, RX_BUF_SIZE * 2, 0, 0, NULL, 0));
    };
}

void init_uart2su03t(void)
{
    if(uart_is_driver_installed(UART_NUM_SU03T) == false){
        ESP_ERROR_CHECK(uart_param_config(UART_NUM_SU03T, &uart2su03t_config));
        ESP_ERROR_CHECK(uart_set_pin(UART_NUM_SU03T, UART_NUM_SU03T_TX, UART_NUM_SU03T_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
        ESP_ERROR_CHECK(uart_driver_install(UART_NUM_SU03T, RX_BUF_SIZE * 2, 0, 0, NULL, 0));
    };
}

void servoUARTread(char *UARTdata)
{
    size_t bufferLenth;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_SERVO, &bufferLenth));
    uart_read_bytes(UART_NUM_SERVO, UARTdata, bufferLenth, 100);
    ESP_ERROR_CHECK(uart_flush(UART_NUM_SERVO));
}

void IDUARTwrite_Bytes(uint8_t data)
{
    uart_write_bytes(UART_NUM_ID, &data, 1);
}


void IDUARTwrite_Bytes(uint16_t data)
{
    uint8_t data1 = data >> 8;
    uart_write_bytes(UART_NUM_ID, &data1, 1);
    uart_write_bytes(UART_NUM_ID, &data, 1);
}

void IDUARTwrite_Bytes(uint32_t data)
{
    uint8_t data1 = data >> 24;
    uint8_t data2 = data >> 16;
    uint8_t data3 = data >> 8;
    uart_write_bytes(UART_NUM_ID, &data1, 1);
    uart_write_bytes(UART_NUM_ID, &data2, 1);
    uart_write_bytes(UART_NUM_ID, &data3, 1);
    uart_write_bytes(UART_NUM_ID, &data, 1);
}

/*******************************************************************************
****函数功能: 串口通信函数
****出口参数: 无
****函数备注: 解析串口接收到的上位机指令
********************************************************************************/
void command_loop(void)
{
  int length = 0;
  uart_get_buffered_data_len(UART_NUM_SCREEN, (size_t*)&length);
  // 如果串口是空的直接返回
  if (length == 0) return;
  char received_chars[10];
  vTaskDelay(1 / portTICK_PERIOD_MS);
  // 从串口读取返回的数据，读取20个字符
  uart_read_bytes(UART_NUM_SCREEN, received_chars, length, 100);

  // 根据指令做不同动作
  if (received_chars[0] == 'F') // F指令设置
  {

  }
  //  最后清空串口
  while (length >= 0)
    uart_flush(UART_NUM_SCREEN);
}