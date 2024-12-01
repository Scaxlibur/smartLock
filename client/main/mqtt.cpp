#include "mqtt.hpp"

// 事件处理函数
 void MQTT_class::mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) 
{
    //printf("Event dispatched from event loop base=%s, event_id=%d \n", base, event_id);
    // 获取MQTT客户端结构体指针
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t) event_data;
    esp_mqtt_client_handle_t client = event->client;
    // 通过事件ID来分别处理对应的事件
    switch (event->event_id) 
    {
        // 建立连接成功
        case MQTT_EVENT_CONNECTED:
            printf("MQTT_client cnnnect to EMQ ok. \n");
            // 发布主题，主题消息为“SmartLock Connected”,自动计算有效载荷，qos=2，即只发送一次
            esp_mqtt_client_publish(client, "SmartLock_publish", "SmartLock Connected", 0, 2, 0);
            // 订阅主题，qos=0
            esp_mqtt_client_subscribe(client, "ESP32_Subscribe", 0);           
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

void MQTT_class::mqtt_app_start(void)
{
    // 1、定义一个MQTT客户端配置结构体，输入MQTT的url
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address = {
                .uri = MQTT_URL,
                .port = 1883,
            }
        },
        .credentials={
            .username = MQTT_USERNAME,
            .authentication={
                .password = MQTT_PASSWORD
            }
        },
    };

    // 2、通过esp_mqtt_client_init获取一个MQTT客户端结构体指针，参数是MQTT客户端配置结构体
    client = esp_mqtt_client_init(&mqtt_cfg);

    // 3、注册MQTT事件
    esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, mqtt_event_handler, client);
    
    // 4、开启MQTT功能
    esp_mqtt_client_start(client);
}


void MQTT_class::sendMessage(const char *data){
    esp_mqtt_client_publish(client, "ESP32_Publish", data, 0, 2, 0);
}

MQTT_class::MQTT_class(){
    mqtt_app_start();
}

MQTT_class::~MQTT_class(){
    
};