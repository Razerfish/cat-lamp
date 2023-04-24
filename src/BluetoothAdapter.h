#ifndef BLUETOOTHADAPTER_H
#define BLUETOOTHADAPTER_H

#include <Arduino.h>

#include "config.h"
#include "Command.h"

class BluetoothAdapter
{
    protected:
        bool initialized;
        uint8_t buffer[BUFSIZE];
        size_t length;

    public:
        virtual bool start();
        virtual Command parseCommand();
        virtual bool commandAvailable();
};

#endif
