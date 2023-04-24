#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>

#include "Utils.h"

class Command
{
    private:
        uint8_t* data;
        size_t length;
        PacketType type;

    public:
        Command(PacketType type, uint8_t data[], size_t length);
        ~Command();
        uint8_t& operator[](int index);
};

#endif
