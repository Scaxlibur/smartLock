#include "su03t.hpp"

SU03T_class::SU03T_class()
{
    gpio_config(&io_conf);
}

bool SU03T_class::manbo(void)
{
    gpio_set_level(GPIO_NUM_14, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(GPIO_NUM_14, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    return true;
}