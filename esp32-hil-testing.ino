#include <PubSubClient.h>
#include "BluetoothSerial.h"

extern const char * mqtt_server;
extern PubSubClient client;
extern BluetoothSerial SerialBT;

void setup() {
    Serial.begin(9600);
    SerialBT.begin("esp32/test");
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    SerialEvent();
    SerialBTEvent();
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
