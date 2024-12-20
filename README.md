# 基于ESP32-S3的高安全性宿舍智能门锁设计

编译环境：ESP-IDF v5.3.1
开发板：ESP32-S3 DevkitC-1

## 主要特性

1. 兼容宿舍门锁：采用串口总线舵机驱动，拉动锁舌开锁
2. 高安全性：利用ESP32-S3的eFuse、世界控制器等特性实现高安全性
3. 人机交互：利用串口屏、喇叭实现人机交互，针对不同的事件播放不同音效
4. 物联网：通过MQTT方式实现回传，记录开锁信息
5. 开锁方式：支持指纹识别

## 文档结构

```text

smartLock
├── .vscode
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── tasks.json
├── main
│   ├── CMakeLists.txt
│   ├── fingerID.cpp
│   ├── fingerID.hpp
│   ├── main.cpp
│   ├── mqtt.cpp
│   ├── mqtt.hpp
│   ├── screen.cpp
│   ├── screen.hpp
│   ├── servo.cpp
│   ├── servo.hpp
│   ├── UARTtrans.cpp
│   └── UARTtrans.hpp
├── server
│   ├── docker-compose.yml
│   └── http_server.py
├── UARTscreenConfig
│   └── UARTscreenConfig.HMI
├── .gitignore
├── CMakeLists.txt
├── License
├── README.md                       This is the file you are currently reading
└── sdkconfig

```
