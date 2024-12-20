#ifndef __SU03T_HPP__
#define __SU03T_HPP__
#pragma once

#include "UARTtrans.hpp"
#include "driver/gpio.h"

#define GPIO_OUTPUT_PIN_SEL  (1ULL<<GPIO_NUM_14)
class SU03T_class
{
private:
    //zero-initialize the config structure.
    gpio_config_t io_conf = {
        .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
    };
public:
    bool manbo(void);

    SU03T_class();                                               //构造函数
    ~SU03T_class();                                                               //析构函数
};

#endif