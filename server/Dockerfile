FROM python
RUN pip install mysql-connector \
    && pip install paho-mqtt
COPY ./MQTT_server.py /app/
ENV MYSQL_DATABASE SmartLockDataBase
ENV MYSQL_ROOT_PASSWORD SmartLockDataBasePassword
CMD "/bin/sh"