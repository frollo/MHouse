#include "grove.h"
#include "jhd1313m1.h"
#include <string.h>
#include <climits>
#include <iostream>
#include <sstream>
#include <unistd.h>
int main(int argc, char**argv)
{
 // check that we are running on Galileo or Edison
 char *stringa1 =argv[1];
 char *stringa2 =argv[2];



 mraa_platform_t platform = mraa_get_platform_type();
 if ((platform != MRAA_INTEL_GALILEO_GEN1) &&
		 (platform != MRAA_INTEL_GALILEO_GEN2) &&
		 (platform != MRAA_INTEL_EDISON_FAB_C)) {
	 	 std::cerr << "Unsupported platform, exiting" << std::endl;
 return MRAA_ERROR_INVALID_PLATFORM;
 }
 upm::Jhd1313m1* lcd = new upm::Jhd1313m1(0);
 	 char *app1,*app2;
 lcd->setCursor(0,0);
 	int ns1,ns2,n;
 	ns1=strlen(stringa1)/16;
 	ns2=strlen(stringa2)/16;
 	 lcd->setColor(255, 64, 255);
 	if(ns1==0 && ns2==0){
 	  lcd->write(stringa1);
 	  lcd->setCursor(1,0);
 	  lcd->write(stringa2);
 	}else{
 		app1=stringa1;
 		app2=stringa2;
 		while(true){
 			lcd->write(app1);
 			lcd->setCursor(1,0);
 			lcd->write(app2);
 			if(strlen(app1)/16!=0){
 				app1=&app1[16];
 			}else{
 				app1=stringa1;
 			}
 			if(strlen(app2)/16!=0){
 			 	app2=&app2[16];
 			 }else{
 			 	app2=stringa2;
 			 }
 			sleep(3);
 			lcd->clear();
 		}

 	}
  return MRAA_SUCCESS;
 }
