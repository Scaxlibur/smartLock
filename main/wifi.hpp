#ifndef __WIFI_HPP__
#define __WIFI_HPP__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "spi_flash_mmap.h"
#include "esp_wifi.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "esp_smartconfig.h"

#include "authorsPrivate.h" 

/* 宏定义WiFi名称和密码,定义于authorsPrivate.H */
#define MY_WIFI_SSID    WIFI_SSID
#define MY_WIFI_PASSWD  WIFI_PASSWD

/* 宏定义WiFi连接事件标志位、连接失败标志位及智能配网标志位 */
#define WIFI_CONNECTED_BIT  BIT0
#define WIFI_FAIL_BIT       BIT1
#define SMART_CONFIG_BIT    BIT2

/* 定义一个WiFi连接事件标志组句柄 */
static EventGroupHandle_t wifi_event_group_handler;

/* 系统事件循环处理函数 */
static void event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);

static void smartconfig_init_start(void);

static void wifi_init_sta(void);

#endif