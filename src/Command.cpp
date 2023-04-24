#include "Command.h"

Command::Command(PacketType type, uint8_t data[], size_t length)
{
    this->type = type;
    this->length = length;
    this->data = new uint8_t[length];

    memcpy(this->data, data, sizeof(data[0]) * length);
}


Command::~Command()
{
    delete[] data;
}


uint8_t& Command::operator[](int index)
{
    if (index < 0 || index >= length)
    {
        Serial.println("Index out of bounds!");
        halt();
    }
    else
    {
        return data[index];
    }
}
