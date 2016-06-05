#ifndef COM_H
#define COM_H

#include <Arduino.h>

class Com {
public:
	static uint64_t last, interval;
	static bool on;
	void init(){
		Serial.begin(115200);//Baudrate doesn't matter as we're on Teensy
	}

	void newLoop(){
		uint64_t now = millis();
		if(now - last > interval){
			on = true;
			last = now;
		}else{
			on = false;
		}
	}

	//static void debug();
};
bool Com::on = true;
uint64_t Com::last = 0;
uint64_t Com::interval = 1000; //ms

#define ComDebug(...) \
	{if(Com::on){ Serial.print(__VA_ARGS__); } }


#endif
