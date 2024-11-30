import json
import paho.mqtt.client as mqtt
import pymysql
"""rc 值	
0	连接成功
1	协议版本错误
2	无效的客户端标识
3	服务器无法使用
4	错误的用户名或密码
5	未经授权
"""
#打开数据库连接
mysql_conn = pymysql.connect(user="xxx",password="xxx",host="xxx",database="xxx",port=3306)
def on_connect(client, userdata, flags, rc):
    return rc
def on_message(client, userdata, publish_msg):
    # data = publishMsg.payload
    # print(json.loads(data))
    msg = publish_msg.payload.decode('unicode')
    print(msg)
    ##存数据到数据库中
    cursor = mysql_conn.cursor()
    insert_sql = 'insert into test (value) VALUES ("%s")' %(msg)
    cursor.execute(insert_sql)
    # 提交到数据库执行
    mysql_conn.commit()
    cursor.close()  # 先关闭游标
def main():
    client = mqtt.Client()
    client.username_pw_set(username='', password='')
    client.on_connect = on_connect
    client.on_message = on_message
    rc = client.connect(host='xxxx', port=1883, keepalive=15)    ##服务器地址信息
    print('rc', rc)
    if rc == 0:
        client.subscribe('SmartLock_publish')    ##订阅主题
    else:
        print('连接失败')
        raise Exception
    # 无限循环收发消息
    client.loop_forever()
if __name__ == '__main__':
    main()