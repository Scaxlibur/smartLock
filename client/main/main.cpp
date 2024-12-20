#include "fingerID.hpp"
#include "screen.hpp"
#include "servo.cpp"
#include "wifi.cpp"
#include "mqtt.cpp"

#define RIGHTFINGER 1
#define WRONGFINGER 2
typedef struct{
    int msg = 0;
}data4Tasks;

TaskHandle_t xTask0;   //任务0的句柄
TaskHandle_t xTask1;   //任务1的句柄

QueueHandle_t ID_mqtt_com_handle;  //指纹识别模块和mqtt的通信队列
QueueHandle_t ID_servo_com_handle;  //指纹识别模块和舵机的通信队列

TaskHandle_t servotask_handle;
TaskHandle_t WIFI_MQTT_task_handle;
TaskHandle_t IDtask_handle;

void servotask(void *arg)
{
    SERVO_class servo;  //创建舵机对象
    printf("舵机对象已创建\n");
    BaseType_t ID_servo_com_status;
    data4Tasks ID_servo_com;

    while (1)
    {
        ID_servo_com_status = xQueueReceive(ID_servo_com_handle, &ID_servo_com.msg, 500/portTICK_PERIOD_MS);  //从队列ID_servo_com中取一条数据
        if(ID_servo_com_status == pdPASS){
            if(ID_servo_com.msg) servo.opendoor();
            printf("舵机已开门\n");
        }
        vTaskDelay(50/portTICK_PERIOD_MS);
    }
}


void WIFI_MQTT_task(void *arg)
{
    /* 初始化非易失性存储库 (NVS) */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    printf("ESP_WIFI_MODE_STA \n");
    wifi_init_sta();
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
    MQTT_class mqtt;

    BaseType_t ID_mqtt_com_status;
    data4Tasks ID_mqtt_com;
    
    while(1) {
        ID_mqtt_com_status = xQueueReceive( ID_mqtt_com_handle, &ID_mqtt_com.msg, 50/portTICK_PERIOD_MS);  //从队列ID_mqtt_com中取一条数据
        if(ID_mqtt_com_status == pdPASS){
            printf("get data OK\n");
            switch (ID_mqtt_com.msg)
            {
            case RIGHTFINGER:
                mqtt.sendMessage("Right finger!");
                break;
            case WRONGFINGER:
                mqtt.sendMessage("Wrong finger!");
                break;
            default:
                break;
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void IDtask(void *arg)
{
    IDENTIFIER_class identifier;        //创建指纹识别器对象    
    data4Tasks ID_mqtt_com;             //创建和mqtt通信的消息队列
    data4Tasks ID_servo_com;
    BaseType_t ID_mqtt_com_status;
    BaseType_t ID_servo_com_status;
    //identifier.Add_FR();
    while (1)
    {
        if(identifier.press_FR() == true){
            ID_mqtt_com.msg = RIGHTFINGER;
            ID_servo_com.msg = 1;
            ID_mqtt_com_status = xQueueSendToFront(ID_mqtt_com_handle, &ID_mqtt_com.msg, 50/portTICK_PERIOD_MS);
            ID_servo_com_status = xQueueSendToFront(ID_servo_com_handle, &ID_servo_com.msg, 50/portTICK_PERIOD_MS);
        }else{
            ID_mqtt_com.msg = WRONGFINGER;
            ID_mqtt_com_status = xQueueSendToFront(ID_mqtt_com_handle, &ID_mqtt_com.msg, 50/portTICK_PERIOD_MS);
        }
        if( ID_mqtt_com_status == pdPASS) {
            printf("send data OK\n");  // 发送正常 
        }
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }    
}

extern "C" void app_main(void)
{
    printf("power on\n");

    ID_mqtt_com_handle = xQueueCreate(10, sizeof(data4Tasks));
    ID_servo_com_handle = xQueueCreate(10, sizeof(data4Tasks));

    //xTaskCreate(servotask, "servotask", 12 * 1024, NULL, 1, &servotask_handle);
    xTaskCreate(IDtask, "idtask", 12 * 1024, NULL, 10, &IDtask_handle);
    //xTaskCreate(WIFI_MQTT_task, "WIFI_MQTT_task", 12 * 1024, NULL, 1, &WIFI_MQTT_task_handle);
}
