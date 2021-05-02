// 
// 
// 

#include "packets.h"


Command parsePackets(uint8_t buffer[BUFSIZE], size_t& end)
{
	Command output;
	size_t dataLength = end + 1;

	if (dataLength < HEADER_LENGTH) // Don't waste time evaluating packets that can't even contain a complete header.
	{
		output.head = PacketType::Incomplete;
	}
	else if (buffer[0] != '!') // Invalid header
	{
		output.head = PacketType::Invalid;
		popPackets(buffer, end, 1); // Discard invalid character.
	}
	else
	{
		bool valid = true;
		size_t len; // Expected length.

		switch (buffer[1]) // Switch on command type.
		{
		case 'C': // Color
			len = COLOR_PACKET_LENGTH;
			output.head = PacketType::Color;
			break;

		case 'V': // Brightness
			len = BRIGHTNESS_PACKET_LENGTH;
			output.head = PacketType::Brightness;
			break;

		case 'W': // Warm white
			len = WARM_WHITE_PACKET_LENGTH;
			output.head = PacketType::White;
			break;

		case 'R': // Rainbow
			len = RAINBOW_PACKET_LENGTH;
			output.head = PacketType::Rainbow;
			break;

		default:
			valid = false;
			break;
		}

		if (valid)
		{
			if (dataLength > len)
			{
				// Starting at buffer[2] read the required amount of data.
				for (int i = HEADER_LENGTH; i < len; i++)
				{
					output.body[i - HEADER_LENGTH] = buffer[i];
				}
				popPackets(buffer, end, len); // Discard read packets.
			}
			else
			{
				output.head = PacketType::Incomplete;
			}
		}
		else
		{
			output.head = PacketType::Invalid;
			popPackets(buffer, end, 2); // Discard invalid header.
		}
	}

	return output;
}


void popPackets(uint8_t buffer[BUFSIZE], size_t& end, size_t count)
{
	if (count >= BUFSIZE)
	{
		memset(buffer, 0, BUFSIZE);
		end = 0;
	}
	else
	{
		for (size_t i = 0; i < count; i++)
		{
			buffer[i] = 0;
			buffer[i] = buffer[i + count];
		}

		memset(&buffer[BUFSIZE - count], 0, count);
		end -= count;
	}
}
