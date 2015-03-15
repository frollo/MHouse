/*
 * Author: Ivan De Cesaris <ivan.de.cesaris@intel.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MHouseLib.h"

/*
 * Grove Starter Kit example
 *
 * Demonstrate the usage of various component types using the UPM library.
 *
 * - digital in: GroveButton connected to the Grove Base Shield Port D4
 * - digital out: GroveLed connected to the Grove Base Shield Port D3
 * - analog in: GroveTemp connected to the Grove Base Shield Port A0
 * - I2C: Jhd1313m1 LCD connected to any I2C on the Grove Base Shield
 *
 * Additional linker flags: -lupm-i2clcd -lupm-grove
 */

/*
 * Update the temperature values and reflect the changes on the LCD
 * - change LCD backlight color based on the measured temperature,
 *   a cooler color for low temperatures, a warmer one for high temperatures
 * - display current temperature
 * - record and display MIN and MAX temperatures
 * - reset MIN and MAX values if the button is being pushed
 * - blink the led to show the temperature was measured and data updated
 */

int setLedOn(int target){
	// check that we are running on Galileo or Edison
	mraa_platform_t platform = mraa_get_platform_type();
	if ((platform != MRAA_INTEL_GALILEO_GEN1) &&
			(platform != MRAA_INTEL_GALILEO_GEN2) &&
			(platform != MRAA_INTEL_EDISON_FAB_C)) {
		std::cerr << "Unsupported platform, exiting" << std::endl;
		return MRAA_ERROR_INVALID_PLATFORM;
	}
	FILE *f=fopen("/home/root/eseguibili/led","w");
	upm::GroveLed* led0 = new upm::GroveLed(2);
	upm::GroveLed* led1 = new upm::GroveLed(3);
	upm::GroveLed* led2= new upm::GroveLed(4);
	switch(target){

	case 1:
		led0->on();
		led1->off();
		led2->off();
		putc('1',f);
		break;

	case 2:
		led0->off();
		led1->on();
		led2->off();
		putc('2',f);
		break;

	case 3:
		led0->off();
		led1->off();
		led2->on();
		putc('3',f);
	}
	fclose(f);
	return MRAA_SUCCESS;
}
