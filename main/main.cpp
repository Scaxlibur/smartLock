#include <stdio.h>
#include "fingerID.hpp"
#include "screen.hpp"
#include "servo.cpp"
#include "wifi.cpp"
#include "mqtt.cpp"
                  
/*
void servotask(void *arg)
{
    SERVO servo;  //创建舵机对象
    printf("舵机对象已创建\n");
    while (1)
    {
        servo.opendoor();
        printf("调用\n");
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}
*/

void WIFItask(void *arg)
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
    while(1) vTaskDelay(10 / portTICK_PERIOD_MS);
}

void MQTTtask(void *arg)
{
    void mqtt_app_start(void);
    while(1) vTaskDelay(10 / portTICK_PERIOD_MS);
}

void IDtask(void *arg)
{
    IDENTIFIER identifier;      //创建指纹识别器对象    
    
    identifier.Add_FR();
    while (1)
    {
        identifier.press_FR();
        #ifdef TEST
        printf("\nIDtask任务调用\n");
        #endif
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }    
}

extern "C" void app_main(void)
{
    printf("power on\n");
    //xTaskCreate(servotask, "servotask", 12 * 1024, NULL, 1, NULL);
    //xTaskCreate(IDtask, "idtask", 12 * 1024, NULL, 1, NULL);
    xTaskCreate(WIFItask, "wifitask", 12 * 1024, NULL, 1, NULL);
    xTaskCreate(MQTTtask, "mqtttask", 12 * 1024, NULL, 1, NULL);
}
