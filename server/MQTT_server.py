import logging
import random
import time
import mysql.connector
import os

#from paho.mqtt import client as mqtt_client
import paho.mqtt.client as mqtt

MYSQL_database = os.environ.get('MYSQL_DATABASE')
MYSQL_password = os.environ.get('MYSQL_ROOT_PASSWORD') #MYSQL数据库和密码

BROKER = '******.ala.cn-hangzhou.emqxsl.cn'  #MQTT地址
PORT = 1883
TOPIC = "python-mqtt/wss"
# generate client ID with pub prefix randomly
CLIENT_ID = f'python-mqtt-wss-sub-{random.randint(0, 1000)}'
USERNAME = '*******'  #你的MQTT用户名
PASSWORD = '*******'  #你的MQTT密码

FIRST_RECONNECT_DELAY = 1
RECONNECT_RATE = 2
MAX_RECONNECT_COUNT = 12
MAX_RECONNECT_DELAY = 60

FLAG_EXIT = False

# 配置数据库连接参数
config = {
    'user': 'root',       # MySQL用户名
    'password': 'environment',   # MySQL密码
    'host': '**********',   # MySQL服务器地址，本地为localhost
    'database': '********', # 需要连接的数据库名
    'raise_on_warnings': True
}

def on_connect(client, userdata, flags, rc):
    if rc == 0 and client.is_connected():
        print("Connected to MQTT Broker!")
        client.subscribe(TOPIC)
    else:
        print(f'Failed to connect, return code {rc}')


def on_disconnect(client, userdata, rc):
    logging.info("Disconnected with result code: %s", rc)
    reconnect_count, reconnect_delay = 0, FIRST_RECONNECT_DELAY
    while reconnect_count < MAX_RECONNECT_COUNT:
        logging.info("Reconnecting in %d seconds...", reconnect_delay)
        time.sleep(reconnect_delay)

        try:
            client.reconnect()
            logging.info("Reconnected successfully!")
            return
        except Exception as err:
            logging.error("%s. Reconnect failed. Retrying...", err)

        reconnect_delay *= RECONNECT_RATE
        reconnect_delay = min(reconnect_delay, MAX_RECONNECT_DELAY)
        reconnect_count += 1
    logging.info("Reconnect failed after %s attempts. Exiting...", reconnect_count)
    global FLAG_EXIT
    FLAG_EXIT = True


def on_message(client, userdata, msg):
    print(f'Received `{msg.payload.decode()}` from `{msg.topic}` topic')
    connect_mysql()


def connect_mqtt():
    client = mqtt.Client(client_id=CLIENT_ID, transport='websockets',callback_api_version=mqtt.CallbackAPIVersion.VERSION1)
    #client = mqtt_client.Client(CLIENT_ID, transport='websockets')
    client.tls_set(ca_certs='./emqxsl-ca.crt')
    client.username_pw_set(USERNAME, PASSWORD)
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(BROKER, PORT, keepalive=120)
    client.on_disconnect = on_disconnect
    return client

def connect_mysql():
    try:
        # 建立数据库连接
        connection = mysql.connector.connect(**config)
        if connection.is_connected():
            db_info = connection.get_server_info()
        print("成功连接到MySQL数据库，版本为：", db_info)
        
        # 创建一个游标对象，用于执行SQL语句
        cursor = connection.cursor()
        

        # 插入数据
        cursor.execute("""
            INSERT INTO cti_ai_chat_logs (initiator, content)
            VALUES ('John Doe', '2222222222222222')
        """)
        
        # 提交事务
        connection.commit()
        
        # 查询数据
        cursor.execute("SELECT * FROM cti_ai_chat_logs")
        for row in cursor:
            print(row)
        
        # 关闭游标
        cursor.close()
        
        # 关闭数据库连接
        connection.close()
        
    except mysql.connector.Error as err:
        print("发生错误：", err)
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()
            print("MySQL连接已关闭")


def run():
    logging.basicConfig(format='%(asctime)s - %(levelname)s: %(message)s',
                        level=logging.DEBUG)
    client = connect_mqtt()
    client.loop_forever()


if __name__ == '__main__':
    run()