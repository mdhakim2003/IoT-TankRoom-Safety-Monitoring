import serial
import time
import json
import paho.mqtt.client as mqtt

# ------------------------
# MQTT Configuration
# ------------------------
BROKER_IP = "10.108.71.197"
BROKER_PORT = 1883
TOPIC = "iot/monitoring/sts1"

# ------------------------
# Serial Configuration
# ------------------------
SERIAL_PORT = "COM2"
BAUD_RATE = 9600

# ------------------------
# Sensor Key Mapping
# Assigning new IDs for DHT and Light sensors
# ------------------------
SENSORS = {
    "temperature": 118,
    "humidity": 119,
    "light": 120
}

# ------------------------
# Setup
# ------------------------
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
client = mqtt.Client(client_id="ArduinoDHTPublisher")
client.connect(BROKER_IP, BROKER_PORT)
client.loop_start()

# ------------------------
# Main Loop
# ------------------------
while True:
    if ser.in_waiting:
        line = ser.readline().decode(errors="ignore").strip()
        parts = line.split(",")

        # Looking for 4 parts: timestamp, temp, hum, light
        if len(parts) == 4:
            try:
                timestamp = int(parts[0])
                temp      = float(parts[1])
                hum       = float(parts[2])
                light     = float(parts[3])

                readings = {
                    SENSORS["temperature"]: temp,
                    SENSORS["humidity"]: hum,
                    SENSORS["light"]: light
                }

                for sensor_key, value in readings.items():
                    payload = {
                        "station_key": "Arduino_DHT_Station",
                        "sensor_key": sensor_key,
                        "value": value,
                        "timestamp": timestamp
                    }

                    client.publish(TOPIC, json.dumps(payload), qos=0)
                    print("Published:", payload)

            except ValueError:
                print("Invalid data format:", line)

    time.sleep(0.2)
