/*
 Name:		AUnit_Tests.ino
 Created:	3/18/2021 4:37:03 PM
 Author:	fiona.wilson
*/

//#include <Adafruit_NeoPixel.h>
#include <AUnitVerbose.h>

// Include files to test here.
#include "lighting.h"
#include "lightingTest.h"

// Define tests here.

test(rainbowGradient)
{
	for (int i = 0; i < RAINBOW_REF_LENGTH; i++)
	{
		assertEqual(rainbowGradient(i * RAINBOW_TEST_INCREMENT, RAINBOW_GRADIENT_LENGTH), rainbowRef[i]);
	}
}


test(colorDimmable)
{
	int
		i,
		j,
		k = 0;

	for (i = 0; i < BRIGHTNESS_COLORS; i++)
	{
		for (j = 0; j < BRIGHTNESS_TEST_LEVELS; j++)
		{
			assertEqual(colorDimmable(brightnessColors[i][0], brightnessColors[i][1], brightnessColors[i][2], brightnessColors[i][3], brightnessLevels[j]), brightnessRef[k]);
			k++;
		}
	}
}


void setup() {
	Serial.begin(115200);
}


void loop()
{
	aunit::TestRunner::run();
}
