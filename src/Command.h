#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>

#include "Utils.h"

enum class PacketType { Color = 43, Brightness = 56, White = 57, Rainbow = 52, Pattern = 50 };

class Command
{
    private:
        uint8_t* data;
        size_t length;
        PacketType type;

    public:
        Command(uint8_t data[], size_t length);
        ~Command();
        uint8_t& operator[](int index);
};

#endif
