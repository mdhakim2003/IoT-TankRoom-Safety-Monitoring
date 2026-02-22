import serial
import time
import json
import paho.mqtt.client as mqtt

# ------------------------
# MQTT Configuration
# ------------------------
BROKER_IP = "10.108.71.197"
BROKER_PORT = 1883
TOPIC = "iot/inspection/sts2"

# ------------------------
# Serial Configuration
# ------------------------
SERIAL_PORT = "COM2"
BAUD_RATE = 9600

# ------------------------
# Sensor Key Mapping
# ------------------------
SENSORS = {
    "occupancy": 121,
    "distance": 122,
    "smoke": 123,
    "fan": 124
}

# ------------------------
# Setup
# ------------------------
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
client = mqtt.Client(client_id="ArduinoOccPublisher")
client.connect(BROKER_IP, BROKER_PORT)
client.loop_start()

# ------------------------
# Main Loop
# ------------------------
while True:
    if ser.in_waiting:
        line = ser.readline().decode(errors="ignore").strip()
        parts = line.split(",")

        if len(parts) == 5:
            try:
                timestamp = int(parts[0])
                occupancy = int(parts[1])
                distance  = float(parts[2])
                smoke     = float(parts[3])
                fan       = int(parts[4])

                readings = {
                    SENSORS["occupancy"]: occupancy,
                    SENSORS["distance"]: distance,
                    SENSORS["smoke"]: smoke,
                    SENSORS["fan"]: fan
                }

                for sensor_key, value in readings.items():
                    payload = {
                        "station_key": "Arduino_Occ01",
                        "sensor_key": sensor_key,
                        "value": value,
                        "timestamp": timestamp
                    }

                    client.publish(TOPIC, json.dumps(payload), qos=0)
                    print("Published:", payload)

            except ValueError:
                print("Invalid data:", line)

    time.sleep(0.2)

