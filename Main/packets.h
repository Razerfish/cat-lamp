// bluetooth.h

#ifndef PACKETS_H
#define PACKETS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"

#define HEADER_LENGTH 2
#define COLOR_PACKET_LENGTH 5
#define BRIGHTNESS_PACKET_LENGTH 3
#define RAINBOW_PACKET_LENGTH 3
#define WARM_WHITE_PACKET_LENGTH 2

enum class PacketType { Color = 43, Brightness = 56, White = 57, Rainbow = 52, Incomplete = 49, Invalid = 0 };

struct Command
{
	PacketType head; // C(0x43) for color, V(0x56) for brightness (B was already taken), W(0x57) for warm white, R(0x52) for rainbow, I(0x49) for incomplete and NUL(0x00) for invalid.
	uint8_t body[3];
};


Command parsePackets(uint8_t buffer[BUFSIZE], size_t& end);
void popPackets(uint8_t buffer[BUFSIZE], size_t& end, size_t count);

#endif

