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

#include "grove.h"
#include "jhd1313m1.h"

#include <climits>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <assert.h>

#include "easywsclient.hpp"
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


using easywsclient::WebSocket;
static WebSocket::pointer ws = NULL;

void handle_message(const std::string & message){
	printf(">>> %s\n", message.c_str());
	//if (message == "world") {
		ws->close();
	//}
}

int main(void){
	using easywsclient::WebSocket;
	WebSocket::pointer ws = WebSocket::from_url("ws://10.2.1.58:8888/manage");
	assert(ws);
	while (true) {
		ws->poll();
	    ws->send("hello");
	    ws->dispatch(handle_message);
	    // ...do more stuff...
	}
	delete ws; // alternatively, use unique_ptr<> if you have C++11
	return 0;
}
