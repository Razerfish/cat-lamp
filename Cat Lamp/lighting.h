// lighting.h

#ifndef _lighting_h
#define _lighting_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

uint32_t colorDimmable(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t brightness);
uint32_t colorDimmable(uint32_t color, uint8_t brightness);

uint32_t rainbowGradient(uint16_t pos, uint16_t length, uint8_t brightness = 255);

#endif

