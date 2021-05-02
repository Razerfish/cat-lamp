#ifndef CONFIG_H
#define CONFIG_H

// BLE SETTINGS
#define BUFSIZE 128
#define VERBOSE_MODE true

#define SPI_CS_PIN 8
#define SPI_IRQ_PIN 7
#define SPI_RST_PIN 4

/*=================================================================================================
		APPLICATION SETTINGS

		FACTORYRESET_ENABLE			Perform a factory reset on the BLE module on startup.
									Good for testing, slows down startup.

		MINIMUM_FIRMWARE_VERSION	Minimum firmware version for the BLE module.

		MODE_LED_BEHAVIOUR			How the LED on the BLE module should behave.
									Valid options are:
									"DISABLE" "MODE" "BLEUART" "HWUART" "SPI" "MANUAL"

		DEVICE_NAME					What the device should advertise itself as.
---------------------------------------------------------------------------------------------------*/
#define FACTORYRESET_ENABLE true
#define MINIMUM_FIRMWARE_VERSION "0.6.6"
#define MODE_LED_BEHAVIOUR "MODE"
#define DEVICE_NAME "Cat Lamp"

// NEOPIXEL SETTINGS
#define LED_PIN 6
#define LED_COUNT 7
#define MAX_BRIGHTNESS 255

#endif
