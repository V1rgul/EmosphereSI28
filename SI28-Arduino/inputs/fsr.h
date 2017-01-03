#ifndef FSR_H
#define FSR_H

#include <Arduino.h>

#include "../com.h"
#include "../filters.h"


#define FSR_PIN A1
#define FSR_MIN 1.18
#define FSR_MAX 2.2F

const bool FSR_DEBUG = 0;

class Fsr {
	float v = 0;
public:
	float out = 0;

	Fsr() {
		//
	}

	void init(){
		pinMode(FSR_PIN, INPUT);
	}

	void read(){
		v = analogRead(FSR_PIN)*3.3/1023;
		if(FSR_DEBUG){ ComDebug(" FSR_R:"); ComDebug(v,4); }
		v = (v-FSR_MIN)/(FSR_MAX-FSR_MIN);
		v = constrain(v, 0, 1);
		if(FSR_DEBUG){ ComDebug(" FSR_V:"); ComDebug(v,4); ComDebug('\n'); }
	}

	void compute(float step){
		out = v;
	}

	void debug(){
		
	}

};

#endif