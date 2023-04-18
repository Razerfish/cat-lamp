/*
 Name:		Main.ino
 Created:	3/29/2021 1:45:57 PM
 Author:	Fiona Wilson
*/

#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_NeoPixel.h>

#include "config.h"
#include "packets.h"
#include "lighting.h"

Adafruit_BluefruitLE_SPI ble(SPI_CS_PIN, SPI_IRQ_PIN, SPI_RST_PIN);

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);


// Stop execution if a fatal error is encountered.
void halt()
{
	while (true);
}


void setup()
{
	// Most of this setup code was adapted from here: https://github.com/adafruit/Adafruit_BluefruitLE_nRF51/blob/master/examples/controller/BluefruitConfig.h

	Serial.begin(115200);
	Serial.println(F("		BLE Cat Lamp		"));
	Serial.println(F("--------------------------"));

	Serial.println(F("Initializing BLE module: "));
	if (!ble.begin(VERBOSE_MODE))
	{
		Serial.println(F("FAILED"));
		halt();
	}
	Serial.println(F("OK!"));

	if (FACTORYRESET_ENABLE)
	{
		Serial.print(F("Performing a factory reset: "));
		if (!ble.factoryReset())
		{
			Serial.println(F("FAILED"));
			halt();
		}
		Serial.println(F("OK!"));
	}

	ble.echo(false);

	Serial.println(F("Requesting Bluefruit info:"));
	ble.info();

	ble.verbose(false);

	if (ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION))
	{
		Serial.println(F("Setting LED activity to " MODE_LED_BEHAVIOUR));
		ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
		Serial.println(F("OK!"));

		Serial.println(F("Setting device name to " DEVICE_NAME));
		ble.sendCommandCheckOK("AT+GAPDEVNAME=" DEVICE_NAME);
		Serial.println(F("OK!"));
	}

	Serial.println(F("Switching to data mode"));
	ble.setMode(BLUEFRUIT_MODE_DATA);
	Serial.println(F("OK!"));
	Serial.println(F("\nReady for connections!"));

	strip.begin();
	strip.show();
	strip.setBrightness(MAX_BRIGHTNESS);
}

void loop()
{
	// Buffer variables
	static uint8_t packetBuf[BUFSIZE];
	static size_t dataEnd = 0;
	bool newData = false;

	// Color & brightness variables
	static uint8_t brightness = 255;
	static uint32_t refColor = 0;

	// Rainbow animation variables
	static uint16_t length = 0;
	static uint16_t pos = 0;
	static bool rainbowActive = false;

	// Misc. variables
	static uint32_t last = 0;
	static bool connStatus = false;

	if (ble.isConnected() != connStatus)
	{
		connStatus = ble.isConnected();
		if (connStatus == true)
		{
			Serial.println(F("Connected"));
		}
		else
		{
			Serial.println(F("Disconnected"));
		}
	}

	if (connStatus == true)
	{
		while (ble.available() && dataEnd < BUFSIZE) // Read new data if there is any available and we have space for it.
		{
			packetBuf[dataEnd] = ble.read();
			dataEnd++;
			newData = true;
		}
	}
	

	if (newData || dataEnd >= BUFSIZE) // Consume packets whenever we recieve new ones or if the buffer is full.
	{
		Command parsed = parsePackets(packetBuf, dataEnd);

		switch (parsed.head)
		{
		case PacketType::Color:
			Serial.print(F("Setting color to: "));
			for (int i = 0; i < 3; i++)
			{
				Serial.print(parsed.body[i], HEX);
				Serial.print(F(", "));
			}
			Serial.println(F("0"));
			Serial.print(F("With brightness: "));
			Serial.println(brightness);

			refColor = colorDimmable(parsed.body[0], parsed.body[1], parsed.body[2], 0, 255);
			strip.fill(colorDimmable(refColor, brightness));
			strip.show();
			rainbowActive = false;
			break;

		case PacketType::Brightness:
			brightness = parsed.body[0];
			Serial.print(F("Setting brightness to: "));
			Serial.println(brightness);

			if (!rainbowActive) // Update color manually if we're not in rainbow mode, in rainbow mode it'll take effect on the next frame
			{
				strip.fill(colorDimmable(refColor, brightness));
				strip.show();
			}
			break;

		case PacketType::White:
			Serial.print(F("Setting warm white with brightness: "));
			Serial.println(brightness);
			strip.fill(colorDimmable(0, 0, 0, 255, brightness));
			strip.show();
			
			rainbowActive = false;
			break;

		case PacketType:: Rainbow:
			Serial.print(F("Starting rainbow cycle with length of "));
			Serial.print(parsed.body[0]);
			Serial.println(F(" seconds"));

			rainbowActive = true;
			length = parsed.body[0] * 60;
			pos = 0;
			break;

		case PacketType::Incomplete:
			Serial.println(F("Incomplete packet"));
			break;

		case PacketType::Invalid:
			Serial.println(F("Invalid packet! Clearing buffer..."));
			memset(packetBuf, 0, BUFSIZE); // Clear buffer of malformed packets.
			dataEnd = 0;
			break;

		default:
			Serial.println(F("I have no idea what is going on"));
			break;
		}
	}

	// Update if in rainbow mode
	if (rainbowActive && millis() - last >= 1000 / 60)
	{
		if (pos > length)
		{
			pos = 0;
		}

		strip.fill(rainbowGradient(pos, length, brightness));
		strip.show();

		pos++;
		last = millis();
	}
}
