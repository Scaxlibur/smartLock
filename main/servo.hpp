#ifndef _servo_HPP
#define _servo_HPP
#pragma once

#include <stdint.h>
#include "UARTtrans.hpp"

class SERVO
{
private:
    char servoID[4] = "000";                                                //舵机编号，默认为000
    
public:
    bool servo_init(void);
    bool opendoor(char resetPos[5] = "0500", char openPos[5] = "2000");
    void setServoID(char out_servoID);
    SERVO(char *out_servoID);                                               //构造函数
    ~SERVO();                                                               //析构函数
    
};

#endif