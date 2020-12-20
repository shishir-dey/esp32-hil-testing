#include "BluetoothSerial.h"
#include <PubSubClient.h>

char BTData;
bool BTStartPacket = false;
String BTDataArray;
bool BTValidPacketFound = false;
char BT_MQTT_BUFFER[100];

BluetoothSerial SerialBT;
extern PubSubClient client;

void SerialBTEvent() {
    if (SerialBT.available()) {
        BTData = SerialBT.read();
        Serial.print(BTData);
        if (BTData == '*' && !BTStartPacket) {
            BTStartPacket = true;
            BTDataArray = "";
            BTDataArray += BTData;
        } else if (BTStartPacket) {
            if (BTData == '#') {
                BTDataArray += BTData;
                BTStartPacket = false;
                BTValidPacketFound = true;
            } else {
                BTDataArray += BTData;
            }
        }

    }
    if (BTValidPacketFound) {
        BTValidPacketFound = false;
        BTDataArray.toCharArray(BT_MQTT_BUFFER, BTDataArray.length() + 1);
        client.publish("esp32/test", BT_MQTT_BUFFER);
    }
}
