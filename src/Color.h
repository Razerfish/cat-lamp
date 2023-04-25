#ifndef COLOR_H
#define COLOR_H

#include <Arduino.h>

class Color
{
    private:
        uint8_t red, green, blue, white;

    public:
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

        void setRed(uint8_t red);
        void setGreen(uint8_t green);
        void setBlue(uint8_t blue);
        void setWhite(uint8_t white);

        uint8_t getRed();
        uint8_t getGreen();
        uint8_t getBlue();
        uint8_t getWhite();
}

#endif
