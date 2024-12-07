import paho.mqtt.client as mqtt
import logging
import random
import time
import mysql.connector
import os

MYSQL_database = os.environ.get('MYSQL_DATABASE')
MYSQL_password = os.environ.get('MYSQL_ROOT_PASSWORD') #MYSQL数据库和密码
MYSQL_address = os.environ.get('MYSQL_ADDRESS')

# MQTT配置
MQTT_BROKER = os.environ.get('MQTT_BROKER')  #MQTT地址
MQTT_PORT = 1883
MQTT_TOPIC = os.environ.get('MQTT_TOPIC')
MQTT_USERNAME = os.environ.get('MQTT_USERNAME')  #你的MQTT用户名
MQTT_PASSWORD = os.environ.get('MQTT_ROOT_PASSWORD')  #你的MQTT密码

# python3.8



# 连接到数据库
#conn = mysql.connector.connect(**db_config)
#cursor = conn.cursor()
# MySQL数据库配置
db_config = {
    'host': MYSQL_address,
    'user': 'root',
    'password': MYSQL_password,  # 替换为你的root密码
    'database': MYSQL_database
}

broker = MQTT_BROKER
port = 1883
topic = MQTT_TOPIC
# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'
username = MQTT_USERNAME
password = MQTT_PASSWORD

def on_connect(client, userdata, flags, reason_code, properties):
    '''客户端从服务器接收到 CONNACK 响应时的回调'''

    print(f"Connected with result code {reason_code}")  # 成功连接时 reason_code 值为 Success

    # 在on_connect()中执行订阅操作，意味着如果应用失去连接并且重新连接后，订阅将被续订。
    if reason_code == 'Success':
        client.subscribe(MQTT_TOPIC)

def on_disconnect(client, userdata, flags, reason_code, properties):
    print(f'Disconnected with result code {reason_code}')


def on_message(client, userdata, msg):
    '''从服务器收到 PUBLISH 消息时的回调。'''
    print(msg.topic + ' ' + str(msg.payload)) # 输出值形如 $SYS/broker/version b'mosquitto version 2.0.18'
    # 插入数据到数据库
    #try:
    #    cursor.execute("INSERT INTO mqtt_messages (message_data) VALUES (%s)", (data,))
    #    conn.commit()
    #except Exception as e:
    #    print("Error saving data to database:", e)

mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_connect = on_connect
mqttc.on_disconnect = on_disconnect
mqttc.on_message = on_message
 
mqttc.username_pw_set(username, password) # 设置访问账号和密码

mqttc.connect(broker, 1883, 60)

# 阻塞调用，处理网络流量、分派回调和处理重新连接
# 有其它提供线程接口和手动接口的loop*()函数可用
mqttc.loop_forever()