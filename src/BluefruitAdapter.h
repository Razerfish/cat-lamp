#ifndef BLUEFRUITADAPTER_H
#define BLUEFRUITADAPTER_H

#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>

#include "config.h"
#include "Utils.h"
#include "BluetoothAdapter.h"

class BluefruitAdapter : public BluetoothAdapter
{
    private:
        Adafruit_BluefruitLE_SPI ble;

        bool initModule();
        bool factoryReset();

    public:
        BluefruitAdapter();
        bool start();
        void poll();
        Command parseCommand();
        bool commandAvailable();
};

#endif
