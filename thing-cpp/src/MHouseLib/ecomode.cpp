/*
, * Author: Ivan De Cesaris <ivan.de.cesaris@intel.com>
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
 * NONINFRINGE
 * MENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MHouseLib.h"

void lightCheck(int lux, upm::GroveLight* light, upm::Jhd1313m1* lcd,upm::GroveLed* led1,upm::GroveLed* led2,upm::GroveLed* led3) {
	// loop forever updating the temperature values every second
	FILE *f=NULL;

	while (true) {
		lux = light->value();
		sleep(1);
		if (lux < 10) {
			lcd->setColor(0, 0, 0);
			led1->off();
			led2->off();
			led3->off();
		} else{
			lcd->setColor(255, 64, 255);
			f=fopen("/home/root/eseguibili/led","r");
			char c=getc(f);
			fclose(f);
			if(c=='1'){
				led1->on();
			}else if(c=='2'){
				led2->on();
			}else if(c=='3'){
				led3->on();
			}

		}
	}
}
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

void eco_thread(void){
	// check that we are running on Galileo or Edison
	mraa_platform_t platform = mraa_get_platform_type();
	if ((platform != MRAA_INTEL_GALILEO_GEN1) &&
			(platform != MRAA_INTEL_GALILEO_GEN2) &&
			(platform != MRAA_INTEL_EDISON_FAB_C)) {
		std::cerr << "Unsupported platform, exiting" << std::endl;
		//return MRAA_ERROR_INVALID_PLATFORM;
		exit (MRAA_ERROR_INVALID_PLATFORM);
	}
	upm::Jhd1313m1* lcd = new upm::Jhd1313m1(0);
	upm::GroveLight* light = new upm::GroveLight(1);
	upm::GroveLed* led0 = new upm::GroveLed(2);
	upm::GroveLed* led1 = new upm::GroveLed(3);
	upm::GroveLed* led2= new upm::GroveLed(4);
	int lux;
  // loop forever updating the temperature values every second
	lightCheck(lux, light, lcd,led0,led1,led2);

	//return MRAA_SUCCESS;
}
