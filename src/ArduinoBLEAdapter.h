#ifndef ARDUINOBLEADAPTER_H
#define ARDUINOBLEADAPTER_H

#include <Arduino.h>

#include "config.h"
#include "Utils.h"
#include "BluetoothAdapter.h"

class ArduinoBLEAdapter : public BluetoothAdapter
{
    public:
        ArduinoBLEAdapter();
}

#endif
