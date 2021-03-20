/*
 Name:		AUnit_Tests.ino
 Created:	3/18/2021 4:37:03 PM
 Author:	fiona.wilson
*/

#include <AUnitVerbose.h>

// Include files to test here.


// Define tests here.


void setup() {
	Serial.begin(115200);
}

void loop() {
	aunit::TestRunner::run();
}
