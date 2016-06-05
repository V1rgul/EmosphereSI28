
#include <Arduino.h>
// #include <Wire.h>

#include "com.h"
#include "inputs/imu.h"
#include "inputs/mic.h"
#include "inputs/fsr.h"
#include "outputs/lfo.h"
#include "outputs/leds.h"
#include "outputs/vibration.h"
#include "outputs/speaker.h"

#include "feelings.h"
#include "feelingsconfig.h"

Com com;
IMU imu;
Mic mic;
Fsr fsr;

FeelingsManager feelingsManager;

LFO lfo;
Leds leds(lfo);
VibrationSoftPWM vibration(lfo);
Speaker speaker(lfo);


typedef uint64_t time64_t;
time64_t time;
time64_t timeNow(){
	return ((time64_t)millis())*1e3 + micros()%1000;
}

void setup() {
	delay(100);
	com.init();
	delay(500);
	ComDebugF("Init...\n");


	//init Leds first
	leds.init();
	leds.setValuesRaw(0,0,0);

	//init others
	imu.init();
	mic.init();
	fsr.init();

	vibration.init();
	speaker.init();

	configFeelings(feelingsManager);


	delay(200);
	time = timeNow();

	ComDebugF("Done!\n");
}

time64_t debugF = 3e6, debugFLast = 0;


void loop() {
	time64_t now = timeNow();
	time64_t timeDiff = now - time;
	time = now;
//	ComDebug("Now:"); ComDebug( ((double)now) / 1e3 , 3 ); ComDebug('\n');

	/////////////// READ ///////////////////////
	imu.read();
	fsr.read();
	mic.read();
	/////////////// COMPUTE ////////////////////
	float step = ((float)timeDiff)/1e6;
	imu.compute(step);
	fsr.compute(step);
	mic.compute(step);
	////////////// SET NEURON //////////////////
	feelingsManager.setInput(FeelingsManager::Inputs::Accel, imu.outL);
	feelingsManager.setInput(FeelingsManager::Inputs::Fsr, fsr.out);
	//feelingsManager.setInput(FeelingsManager::Inputs::Mic, mic.out);
	////////////// DO IT
	feelingsManager.compute();
	////////////// SET OUTPUT //////////////////
	lfo.setValue(feelingsManager.getOutput(FeelingsManager::Outputs::Freq), step);
	leds.setValue(
		feelingsManager.getOutput(FeelingsManager::Outputs::LightHue),
		feelingsManager.getOutput(FeelingsManager::Outputs::LightSat),
		feelingsManager.getOutput(FeelingsManager::Outputs::LightLFOGain),
		feelingsManager.getOutput(FeelingsManager::Outputs::LightLFOWaveform)
	);
	vibration.setValue(
		feelingsManager.getOutput(FeelingsManager::Outputs::VibrateStrengh),
		feelingsManager.getOutput(FeelingsManager::Outputs::VibrateLFOGain),
		feelingsManager.getOutput(FeelingsManager::Outputs::VibrateLFOWaveform)
	);
	speaker.setValue(
		feelingsManager.getOutput(FeelingsManager::Outputs::SoundResp),
		feelingsManager.getOutput(FeelingsManager::Outputs::SoundVNR)
	);

	feelingsManager.debug();
	//delay(100);
	com.newLoop();
}
