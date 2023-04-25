#include "BluefruitAdapter.h"

BluefruitAdapter::BluefruitAdapter() : ble(SPI_CS_PIN, SPI_IRQ_PIN, SPI_RST_PIN)
{
    initialized = false;
    length = BUFSIZE;
    memset(buffer, 0, length);
    dataEnd = 0;
}


bool BluefruitAdapter::initModule()
{
    Serial.println(F("		BLE Cat Lamp		"));
	Serial.println(F("--------------------------"));

	Serial.println(F("Initializing BLE module: "));
	if (!ble.begin(VERBOSE_MODE))
	{
		Serial.println(F("FAILED"));
		return false;
	}
	Serial.println(F("OK!"));
    return true;
}


bool BluefruitAdapter::factoryReset()
{
    Serial.print(F("Performing a factory reset: "));
    if (!ble.factoryReset())
    {
        Serial.println(F("FAILED"));
        return false;
    }
    Serial.println(F("OK!"));
    return true;
}


bool BluefruitAdapter::start()
{
    if (!initModule())
        return false;

    if (FACTORYRESET_ENABLE)
    {
        if (!factoryReset())
            return false;
    }

    ble.echo(false);

    Serial.println(F("Requesting Bluefruit info:"));
    ble.info();

    ble.verbose(false);

    if (!ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION))
        return false;

    Serial.println(F("Setting LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
    Serial.println(F("OK!"));

    Serial.println(F("Setting device name to " DEVICE_NAME));
    ble.sendCommandCheckOK("AT+GAPDEVNAME=" DEVICE_NAME);
    Serial.println(F("OK!"));

    Serial.println(F("Switching to data mode"));
	ble.setMode(BLUEFRUIT_MODE_DATA);
	Serial.println(F("OK!"));
	Serial.println(F("\nReady for connections!"));

    return true;
}


Command BluefruitAdapter::parseCommand()
{

}
