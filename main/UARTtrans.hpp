#ifndef _UARTtrans_HPP
#define _UARTtrans_HPP
#pragma once

#include "driver/uart.h" 
#include <string.h>

/*测试用*/
#define UART_NUM_ID UART_NUM_0
#define UART_NUM_SCREEN UART_NUM_0
#define UART_NUM_SERVO UART_NUM_0

//#define UART_NUM_ID UART_NUM_0
#define UART_NUM_ID_TX UART_PIN_NO_CHANGE
#define UART_NUM_ID_RX UART_PIN_NO_CHANGE
//#define UART_NUM_SCREEN UART_NUM_1
#define UART_NUM_SCREEN_TX UART_PIN_NO_CHANGE
#define UART_NUM_SCREEN_RX UART_PIN_NO_CHANGE
//#define UART_NUM_SERVO UART_NUM_2
#define UART_NUM_SERVO_TX UART_PIN_NO_CHANGE
#define UART_NUM_SERVO_RX UART_PIN_NO_CHANGE

#define READ_WAIT_TICK (1000/portTICK_PERIOD_MS)

void init_uart2id(void);
void init_uart2screen(void);
void init_uart2servo(void);

void strConnect();  //拼接字符串，便于构建串口指令
void servoUARTread(char *UARTdata);                                                                                                         //接受舵机回值

#endif