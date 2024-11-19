#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
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
// 事件处理函数
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) 
{
    //printf("Event dispatched from event loop base=%s, event_id=%d \n", base, event_id);
    // 获取MQTT客户端结构体指针
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    // 通过事件ID来分别处理对应的事件
    switch (event->event_id) 
    {
        // 建立连接成功
        case MQTT_EVENT_CONNECTED:
            printf("MQTT_client cnnnect to EMQ ok. \n");          
            esp_mqtt_client_publish(client, "domoticz/out", "I am ESP32.", 0, 1, 0);
            // 订阅主题，qos=0
            esp_mqtt_client_subscribe(client, "domoticz/out", 0);           
            break;
        // 客户端断开连接
        case MQTT_EVENT_DISCONNECTED:
            printf("MQTT_client have disconnected. \n");
            break;
        // 主题订阅成功
        case MQTT_EVENT_SUBSCRIBED:
            printf("mqtt subscribe ok. msg_id = %d \n",event->msg_id);
            break;
        // 取消订阅
        case MQTT_EVENT_UNSUBSCRIBED:
            printf("mqtt unsubscribe ok. msg_id = %d \n",event->msg_id);
            break;
        //  主题发布成功
        case MQTT_EVENT_PUBLISHED:
            printf("mqtt published ok. msg_id = %d \n",event->msg_id);
            break;
        // 已收到订阅的主题消息
        case MQTT_EVENT_DATA:
            printf("mqtt received topic: %.*s \n",event->topic_len, event->topic);
            printf("topic data: %.*s\r\n", event->data_len, event->data);
            break;
        // 客户端遇到错误
        case MQTT_EVENT_ERROR:
            printf("MQTT_EVENT_ERROR \n");
            break;
        default:
            printf("Other event id:%d \n", event->event_id);
            break;
    }
}

void mqtt_app_start(void)
{
    // 1、定义一个MQTT客户端配置结构体，输入MQTT的url
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://xxx.xxx.xxx.xxx",// ip地址
        .broker.address.port = 1883,
        .credentials.username = "ESP32S3"
        //.alpn_protos,
        // .use_secure_element
    };

    // 2、通过esp_mqtt_client_init获取一个MQTT客户端结构体指针，参数是MQTT客户端配置结构体
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);

    // 3、注册MQTT事件

    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);

    // 4、开启MQTT功能
    esp_mqtt_client_start(client);
}

