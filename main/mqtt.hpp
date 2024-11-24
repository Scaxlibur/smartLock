#ifndef __MQTT_HPP__
#define __MQTT_HPP__
#pragma once

#include <sys/param.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "mqtt_client.h"
#include "driver/gpio.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "wifi.hpp"
#include "authorsPrivate.h"

// 事件处理函数
class MQTT_class{
    private:
    esp_mqtt_client_handle_t client;

    static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
    void mqtt_app_start(void);

    public:
    MQTT_class();
    ~MQTT_class();
    void MQTTsendMessage(const char *data);
};

#endif