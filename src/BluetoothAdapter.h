#ifndef BLUETOOTHADAPTER_H
#define BLUETOOTHADAPTER_H

#include <Arduino.h>

#include "config.h"
#include "Command.h"

#define HEADER_STARTER 21
#define HEADER_LENGTH 2
#define COLOR_PACKET_LENGTH 5
#define BRIGHTNESS_PACKET_LENGTH 3
#define RAINBOW_PACKET_LENGTH 3
#define WARM_WHITE_PACKET_LENGTH 2

class BluetoothAdapter
{
    protected:
        bool initialized;
        uint8_t buffer[BUFSIZE];
        size_t length;
        size_t dataEnd;

        void popPackets(unsigned int count);
        Command invalidCommand();

    public:
        virtual bool start();
        virtual void poll();
        Command parseCommand();
};

#endif
