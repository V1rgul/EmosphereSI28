#ifndef VIBRATION_H
#define VIBRATION_H

#define VIBRATION_PIN 12
#define VIBRATION_MAX 1.0F
#define VIBRATION_THERSHOLD 0.03F

class Vibration {
protected:
	LFO const &lfo;

public:
	Vibration(LFO const &l) :
		lfo(l) {
	}
	void init(){
		pinMode(VIBRATION_PIN, OUTPUT);
	}
	void setValue(float strengh, float lfoGain, float lfoWaveform){
		float v = max(0,strengh-VIBRATION_THERSHOLD) * lfo.computeForm(lfoWaveform, lfoGain) * VIBRATION_MAX;
		analogWrite(VIBRATION_PIN, v*1024);
	}
};


//forgot to put the motor on a PWM PIN ... :/

#include <SoftPWM.h>
#include <SoftPWM_timer.h>

class VibrationSoftPWM : public Vibration {
public:
	VibrationSoftPWM(LFO const &l) :
		Vibration(l)  {
	}
	void init(){
		SoftPWMBegin(SOFTPWM_NORMAL);
	}
	void setValue(float strengh, float lfoGain, float lfoWaveform){
		float v = max(0,strengh-VIBRATION_THERSHOLD) * lfo.computeForm(lfoWaveform, lfoGain) * VIBRATION_MAX;
		SoftPWMSet(VIBRATION_PIN, v*255);
	}
};


#endif