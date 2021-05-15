#include "BluetoothSerial.h"

extern BluetoothSerial SerialBT;

void SerialEvent()
{
    if (Serial.available())
    {
        SerialBT.print(Serial.read());
    }
}
