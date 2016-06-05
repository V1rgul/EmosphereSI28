#ifndef MIC_H
#define MIC_H

#include <Arduino.h>

#include "../com.h"
#include "../filters.h"

#define MIC_PIN A0
#define MIC_MIN .3
#define MIC_MAX .6
#define MIC_GAMMA .5

#define MIC_ENVDETECT .1

const bool MIC_DEBUG = 0;

class Mic {
	EnveloppeDetect ed;

public:
	float v;
	float out = 0;

	Mic() :
		ed(MIC_ENVDETECT) {
		//
	}

	void init(){
		pinMode(MIC_PIN, INPUT);
	}

	void read(){
		v = analogRead(MIC_PIN)*3.3/1023;
		if(MIC_DEBUG){ ComDebug(" MIC_R:"); ComDebug(v,4); }
		v = (v-MIC_MIN)/(MIC_MAX-MIC_MIN);
		if(MIC_DEBUG){ ComDebug(" MIC_V:"); ComDebug(v,4); ComDebug('\n'); }
	}

	void compute(float step){
		ed.next( v, step );
		out = pow(ed.out, MIC_GAMMA);
	}

	void debug(){
		ComDebug(" MIC_PDm:"); ComDebug(ed.pdMin);
		ComDebug(" MIC_PDM:"); ComDebug(ed.pdMax);
		ComDebug(" MIC_OUT:"); ComDebug(out);
		ComDebug('\n');
	}

};

#endif