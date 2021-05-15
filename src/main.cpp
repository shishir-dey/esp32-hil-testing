#include <Arduino.h>
#include "BluetoothSerial.h"

extern BluetoothSerial SerialBT;

void WiFi_Init();
void SerialEvent();
void SerialBTEvent();

void setup()
{
    Serial.begin(9600);
    SerialBT.begin("esp32/test");
    Serial.printf("\nSerial port...9.6KB/s\n");
    SerialBT.printf("Serial port...9.6KB/s\n");
    Serial.printf("Bluetooth serial...9.6KB/s\n");
    SerialBT.printf("Bluetooth serial...9.6KB/s\n");
    // WiFi_Init();
}

void loop()
{
    SerialEvent();
    SerialBTEvent();
}
