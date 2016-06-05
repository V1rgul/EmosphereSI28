#ifndef SPEAKER_H
#define SPEAKER_H

#define SPEAKER_VOL_MAX .05F

// #define SPEAKER_S1_FREQ_MIN 300.0F
// #define SPEAKER_S1_FREQ_MAX 1000.0F
// #define SPEAKER_S2_FREQ_MIN 600.0F
// #define SPEAKER_S2_FREQ_MAX 8000.0F
#define SPEAKER_NL_FREQ_MIN 600.0F
#define SPEAKER_NL_FREQ_MAX 8000.0F
#define SPEAKER_NL_VOL 1.0F

#include <Audio.h>
#include <Wire.h>

AudioSynthWaveformSine sine1;
AudioSynthWaveformSine sine2;
AudioSynthNoiseWhite noise;
AudioFilterBiquad noiseCurve;
AudioMixer4 master;
AudioFilterBiquad masterCurve;
AudioOutputAnalog dac;
AudioConnection patchCordm(master, masterCurve);
AudioConnection patchCordmc(masterCurve, dac);
AudioConnection patchCordSine1(sine1, 0, master, 0);
AudioConnection patchCordSine2(sine2, 0, master, 1);
AudioConnection patchCordNoise(noise, noiseCurve);
AudioConnection patchCordNoiseCurve(noiseCurve, 0, master, 2);

class Speaker {
protected:
	LFO const &lfo;
	float scaleLog(float v, float max, float min){ //take 0->1 and return [min:max] on log scale
		return min * pow(max/min, v);
	}

public:
	Speaker(LFO const &l) :
		lfo(l) {
	}
	void init(){
		AudioMemory(10);
		masterCurve.setNotch(0, 480, 1); //cutoff ugly resonent frequency
		master.gain(0, SPEAKER_VOL_MAX);
		master.gain(1, SPEAKER_VOL_MAX);
		master.gain(2, SPEAKER_VOL_MAX*SPEAKER_NL_VOL);
		// master.gain(3, SPEAKER_VOL_MAX);

		// sine1.amplitude(1);
		// sine2.amplitude(1);
		sine1.frequency(900);
		sine2.frequency(3000);
		// noise.amplitude(1);
	}

	void setValue(float sleep, float vnr){
		float sineA = vnr * lfo.computeForm(0, 1);
		sine1.amplitude(sineA);
		sine2.amplitude(sineA);
		float noiseV = lfo.computeForm(1, 1);
		noise.amplitude(sleep*noiseV);
		noiseCurve.setLowpass(0, scaleLog(1-noiseV, SPEAKER_NL_FREQ_MIN, SPEAKER_NL_FREQ_MAX), 1);
	}
};

#endif