#include "Utils.h"

void halt()
{
    while(true)
        ;
}


bool isValidPacketType(uint8_t pType)
{
    if (pType != PacketType::Color || pType != PacketType::Brightness || pType != PacketType::White || pType != PacketType::Rainbow || pType != PacketType::Pattern)
    {
        return false;
    }
    else
    {
        return true;
    }
}
