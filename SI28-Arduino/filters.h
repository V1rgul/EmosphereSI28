#ifndef FILTER_H
#define FILTER_H

#define MATH_PI 3.14159F

//#include "Arduino.h"

class TimeFilter {
protected:
	float rc;
public:
	float out;

	TimeFilter(float f){
		rc = 1 / (2*MATH_PI*f);
		out = 0;
	}

	void next(float v, float step); //step in s
};

class Lowpass : public TimeFilter {
public:
	Lowpass(float f) :
		TimeFilter(f) {
	}
	void next(float v, float step){
		float a = step / (rc+step);
		out = (1-a)*out + a*v;
	}
};

class Highpass : public TimeFilter {
protected:
	float last = 0;
public:
	Highpass(float f) :
		TimeFilter(f) {
	}
	void next(float v, float step){
		float a = rc / (rc+step);
		out = a * ( out + v - last );
		last = v;
	}
};

class PeakDetect : public Lowpass {
public:
	PeakDetect(float f) :
		Lowpass(f) {
	}

	void next(float v, float step){
		if(v > out) out = v;
		else {
			Lowpass::next(v, step);
		}
	}
};

class EnveloppeDetect : public TimeFilter {
public:
	float pdMin, pdMax;
public:
	EnveloppeDetect(float f) :
		TimeFilter(f) {
		pdMin = pdMax = 0;
	}
	void next(float v, float step){
		float a = step / (rc+step);
		if        ( v > pdMax ) { // v > pdMax
			pdMax = v;
			pdMin = (1-a)*pdMin + a*v;
		} else if ( v < pdMin ) { // pdMin > v
			pdMin = v;
			pdMax = (1-a)*pdMax + a*v;
		} else {
			pdMin = (1-a)*pdMin + a*v;
			pdMax = (1-a)*pdMax + a*v;
		}
		out = pdMax - pdMin;
	}
};




#endif