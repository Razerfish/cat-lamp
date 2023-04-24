#include "BluetoothAdapter.h"

void BluetoothAdapter::popPackets(unsigned int count)
{
    if (count > length)
    {
        memset(buffer, 0, length);
        dataEnd = 0;
    }
    else
    {
        for (size_t i = 0; i < count; i++)
        {
            buffer[i] = buffer[i + 1];
        }
        memset(buffer + count, 0, count);
        dataEnd -= count;
    }
}


Command BluetoothAdapter::invalidCommand()
{
    uint8_t dummyData[1] = {0};
    return Command(PacketType::Invalid, dummyData, 1);
}


Command BluetoothAdapter::parseCommand()
{
    size_t dataLength = dataEnd + 1;

    if (dataLength < HEADER_LENGTH)
        return invalidCommand();

    // Clear the buffer of malformed headers
    while (buffer[0] != HEADER_STARTER)
    {
        popPackets(1);

        if (dataEnd == 0)
            return invalidCommand();
    }
    while (!isValidPacketType(buffer[1]))
    {
        popPackets(2);

        if (dataEnd <= 1)
            return invalidCommand();
    }

    bool valid = true;
    PacketType type;
    size_t len;

    switch (buffer[1])
    {
    case PacketType::Color:
        len = COLOR_PACKET_LENGTH;
        type = PacketType::Color;
        break;

    case PacketType::Brightness:
        len = BRIGHTNESS_PACKET_LENGTH;
        type = PacketType::Color;
        break;

    case PacketType::White:
        len = WARM_WHITE_PACKET_LENGTH;
        type = PacketType::White;
        break;

    case PacketType::Rainbow:
        len = RAINBOW_PACKET_LENGTH;
        type = PacketType::Rainbow;
        break;
    
    default:
        valid = false;
        break;
    }

    if (valid)
    {
        if (dataLength > len)
        {
            Command output = Command(type, len - HEADER_LENGTH);

            for (int i = HEADER_LENGTH; i < len; i++)
            {
                output[i - HEADER_LENGTH] = buffer[i];
            }
            popPackets(len);
            return output;
        }
        else
        {
            return invalidCommand();
        }
    }
}

