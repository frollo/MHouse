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
#include <pthread.h>

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
static const char *type = "THING";

void handle_message(const std::string & message){
	printf(">>> %s\n", message.c_str());
	//if (message == "world") {
		ws->close();
	//}
}


/*
 * The Hamelin thread, which takes care of listening to the
 * steward server
 *
 */
void *hamelin_thread(void *message_handler){
	while (true) {
			ws->poll();
		    ws->send("hello");
		    ws->dispatch(message_handler);
		    // ...do more stuff...
		}
}


/*
 * The specific thread for the Thing
 */
void *specific_thread(void *something){
	while(true){} //Replace with generic implementation
}

int main(char *steward){
	using easywsclient::WebSocket;
	pthread_t threads[2];
	int rc;
	void *sp_thread_args;

	//Connection setup
	WebSocket::pointer ws = WebSocket::from_url(steward);
	assert(ws);

	//Hamelin thread setup
	rc = pthread_create(&threads[0], NULL, hamelin_thread, handle_message);
	if(rc != 0){
		fprintf(stderr, "%s-server: pthread %d\n", type, rc);
		delete ws;
		for(;;){} //loop
	}

	//Specific thread setup
	rc = pthread_create(&threads[1], NULL, specific_thread, sp_thread_args);
		if(rc != 0){
			fprintf(stderr, "%s-server: pthread %d\n", type, rc);
			pthread_cancel(threads[0]); //Kill the Hamelin thread
			delete ws;
			for(;;){} //loop
		}

	delete ws; // alternatively, use unique_ptr<> if you have C++11
	return 0;
}
