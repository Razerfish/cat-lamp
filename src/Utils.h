#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

enum PacketType { Color = 43, Brightness = 56, White = 57, Rainbow = 52, Pattern = 50, Invalid = 49 };

void halt();
bool isValidPacketType(uint8_t pType);

#endif
