// 
// 
// 

#include "lighting.h"

uint32_t colorDimmable(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t brightness)
{
	float ratio = brightness / 255.0f;

	r *= ratio;
	g *= ratio;
	b *= ratio;
	w *= ratio;

	return ((uint32_t)w << 26) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}


uint32_t rainbowGradient(uint16_t pos, uint16_t length, uint8_t brightness)
{
	float ratio = float(pos) / float(length);

	// Find our precise location in a 6 sector gradient with each sector being 256 units long
	uint16_t normalized = ratio * 256 * 6;

	// Find the distance from the start of our sector
	uint16_t range = normalized % 256;

	uint8_t r, g, b;

	// Switch depending on which sector we're in
	switch (normalized / 256)
	{
	case 0: // Red(255, 0, 0) -> Yellow (255, 255, 0)
		r = 255;
		g = range;
		b = 0;
		break;
	case 1: // Yellow(255, 255, 0) -> Green(0, 255, 0)
		r = 255 - range;
		g = 255;
		b = 0;
		break;
	case 2: // Green(0, 255, 0) -> Cyan(0, 255, 255)
		r = 0;
		g = 255;
		b = range;
		break;
	case 3: // Cyan(0, 255, 255) -> Blue(0, 0, 255)
		r = 0;
		g = 255 - range;
		b = 255;
		break;
	case 4: // Blue(0, 0, 255) -> Magenta(255, 0, 255)
		r = range;
		g = 0;
		b = 255;
		break;
	case 5: // Magenta(255, 0, 255) -> Red(255, 0, 0)
		r = 255;
		g = 0;
		b = 255 - range;
		break;
	}

	return colorDimmable(r, g, b, 0, brightness);
}
