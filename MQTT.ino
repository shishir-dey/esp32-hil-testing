#include <PubSubClient.h>
#include "BluetoothSerial.h"
#include <WiFi.h>

const char * mqtt_server = ""; // fill here
const char * mqtt_username = ""; // fill here
const char * mqtt_password = ""; // fill here

extern WiFiClient espClient;
PubSubClient client(espClient);
extern BluetoothSerial SerialBT;
long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char * topic, byte * message, unsigned int length) {
//    Serial.print("Message arrived on topic: ");
//    Serial.print(topic);
//    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++) {
        Serial.print((char) message[i]);
        messageTemp += (char) message[i];
    }
    Serial.println();
    if (String(topic) == "esp32/test") {
        Serial.println(messageTemp);
        SerialBT.println(messageTemp);
    }
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
            Serial.println("connected");
            // Subscribe
            client.subscribe("esp32/test");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
