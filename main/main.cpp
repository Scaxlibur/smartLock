#include <stdio.h>
#include "fingerID.hpp"
#include "screen.hpp"

extern "C" void app_main(void)
{
    /*现在都是测试*/
    printf("开机了");
    init_uart2id();
    //while(1){
    char test[6] = "1234\n";
    while(1){
        uart_write_bytes(UART_NUM_ID, test, sizeof(test));//
        vTaskDelay(100);
    }
}
