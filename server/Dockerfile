FROM python
RUN pip install mysql-connector \
    && pip install paho-mqtt
COPY ./MQTT_server.py /app/
ENV MYSQL_DATABASE = SmartLockDataBase\
    MYSQL_ROOT_PASSWORD = SmartLockDataBasePassword