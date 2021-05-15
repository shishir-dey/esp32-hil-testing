#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void SerialBTEvent()
{
    if (SerialBT.available())
    {
        Serial.print(SerialBT.read());
    }
}
