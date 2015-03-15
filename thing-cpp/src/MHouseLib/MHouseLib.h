/*
 * MHouseLib.h
 *
 *  Created on: 15/mar/2015
 *      Author: frollo
 */

#ifndef SRC_MHOUSELIB_MHOUSELIB_H_
#define SRC_MHOUSELIB_MHOUSELIB_H_

#include "grove.h"
#include <climits>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "jhd1313m1.h"
#include <string.h>

int setLedOn(int target);
void eco_thread(void);
int print_to_LCD(char *stringa1, char *stringa2);
int temperature();


#endif /* SRC_MHOUSELIB_MHOUSELIB_H_ */
