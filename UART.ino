#include <PubSubClient.h>
#include "BluetoothSerial.h"

char SerialData;
bool SerialStartPacket = false;
String SerialDataArray;
bool SerialValidPacketFound = false;
char Serial_MQTT_BUFFER[100];

extern PubSubClient client;
extern BluetoothSerial SerialBT;

void SerialEvent() {
    if (Serial.available()) {
        SerialData = Serial.read();
        SerialBT.print(SerialData);
        if (SerialData == '*' && !SerialStartPacket) {
            SerialStartPacket = true;
            SerialDataArray = "";
            SerialDataArray += SerialData;
        } else if (SerialStartPacket) {
            if (SerialData == '#') {
                SerialDataArray += SerialData;
                SerialStartPacket = false;
                SerialValidPacketFound = true;
            } else {
                SerialDataArray += SerialData;
            }
        }

    }
    if (SerialValidPacketFound) {
        SerialValidPacketFound = false;
        SerialDataArray.toCharArray(Serial_MQTT_BUFFER, SerialDataArray.length() + 1);
        client.publish("esp32/test", Serial_MQTT_BUFFER);
    }
}
