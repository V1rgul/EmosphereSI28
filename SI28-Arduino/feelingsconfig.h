#ifndef FEELINGSCONFIG_H
#define FEELINGSCONFIG_H

#include "feelings.h"


void configFeelings(FeelingsManager &m){

	m.setFeelingsGamma(3);

	m.setSpecificGamma(FeelingsManager::Outputs::LightHue, 10);
	m.setSpecificGamma(FeelingsManager::Outputs::SoundVNR, 5);

	///// RAGE /////////////////////////////////////////////////////////////////////////////////
	m.setI(FeelingsManager::Feelings::Rage, FeelingsManager::Inputs::Fsr,	1.0, 1.0);
	m.setI(FeelingsManager::Feelings::Rage, FeelingsManager::Inputs::Accel,	1.0, 1.0);
	//m.setInputTarget(FeelingsManager::Inputs::Mic,	FeelingsManager::Feelings::Rage,	1, 1);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::Freq,	1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::LightHue,			  0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::LightSat,			1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::LightLFOGain,		1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::LightLFOWaveform,	  0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::VibrateStrengh,		1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::VibrateLFOGain,		1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::VibrateLFOWaveform,	  0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::SoundResp,	   .0, 1.0);
	m.setO(FeelingsManager::Feelings::Rage,	FeelingsManager::Outputs::SoundVNR,		  1.0, 1.0);

	///// FEAR /////////////////////////////////////////////////////////////////////////////////
	m.setI(FeelingsManager::Feelings::Fear, FeelingsManager::Inputs::Fsr,	1.0, 1.0);
	m.setI(FeelingsManager::Feelings::Fear, FeelingsManager::Inputs::Accel,	  0, 1.0);
	//m.setInputTarget(FeelingsManager::Inputs::Mic,	FeelingsManager::Feelings::Rage,	1, 1);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::Freq,	1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::LightHue,			 .7, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::LightSat,			1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::LightLFOGain,		 .5, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::LightLFOWaveform,	1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::VibrateStrengh,		 .4, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::VibrateLFOGain,		 .5, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::VibrateLFOWaveform,	1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::SoundResp,	   .0, 1.0);
	m.setO(FeelingsManager::Feelings::Fear, FeelingsManager::Outputs::SoundVNR,		   .0, 1.0);

	///// JOY /////////////////////////////////////////////////////////////////////////////////
	m.setI(FeelingsManager::Feelings::Joy, FeelingsManager::Inputs::Fsr,	 .3, 1.0);
	m.setI(FeelingsManager::Feelings::Joy, FeelingsManager::Inputs::Accel,	 .8, 1.0);
	//m.setInputTarget(FeelingsManager::Inputs::Mic,	FeelingsManager::Feelings::Rage,	1, 1);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::Freq,	.5, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::LightHue,			 .2, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::LightSat,			1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::LightLFOGain,		 .5, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::LightLFOWaveform,	  0, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::VibrateStrengh,		 .5, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::VibrateLFOGain,		 .5, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::VibrateLFOWaveform,	  0, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::SoundResp,	   .0, 1.0);
	m.setO(FeelingsManager::Feelings::Joy, FeelingsManager::Outputs::SoundVNR,		   .0, 1.0);

	///// LOVE /////////////////////////////////////////////////////////////////////////////////
	m.setI(FeelingsManager::Feelings::Love, FeelingsManager::Inputs::Fsr,	  0, 1.0);
	m.setI(FeelingsManager::Feelings::Love, FeelingsManager::Inputs::Accel,	 .35, 1.0);
	//m.setInputTarget(FeelingsManager::Inputs::Mic,	FeelingsManager::Feelings::Rage,	1, 1);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::Freq,	 .2, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::LightHue,			 .9, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::LightSat,			 .7, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::LightLFOGain,		 .5, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::LightLFOWaveform,	1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::VibrateStrengh,		 .2, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::VibrateLFOGain,		 .5, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::VibrateLFOWaveform,	  0, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::SoundResp,	   .3, 1.0);
	m.setO(FeelingsManager::Feelings::Love, FeelingsManager::Outputs::SoundVNR,		   .0, 1.0);

	// ///// SAD  /////////////////////////////////////////////////////////////////////////////////
	// m.setI(FeelingsManager::Feelings::Sad, FeelingsManager::Inputs::Fsr,	  0, 1.0);
	// m.setI(FeelingsManager::Feelings::Sad, FeelingsManager::Inputs::Accel,	 .5, 1.0);
	// //m.setInputTarget(FeelingsManager::Inputs::Mic,	FeelingsManager::Feelings::Rage,	1, 1);
	// m.setO(FeelingsManager::Feelings::Sad, FeelingsManager::Outputs::Freq,	 .2, 1.0);
	// m.setO(FeelingsManager::Feelings::Sad, FeelingsManager::Outputs::LightHue,			 .9, 2.0);
	// m.setO(FeelingsManager::Feelings::Sad, FeelingsManager::Outputs::LightSat,			 .7, 1.0);
	// m.setO(FeelingsManager::Feelings::Sad, FeelingsManager::Outputs::LightLFOGain,		 .5, 1.0);
	// m.setO(FeelingsManager::Feelings::Sad, FeelingsManager::Outputs::LightLFOWaveform,	1.0, 1.0);
	// m.setO(FeelingsManager::Feelings::Sad, FeelingsManager::Outputs::VibrateStrengh,		 .3, 1.0);
	// m.setO(FeelingsManager::Feelings::Sad, FeelingsManager::Outputs::VibrateLFOGain,		 .5, 1.0);
	// m.setO(FeelingsManager::Feelings::Sad, FeelingsManager::Outputs::VibrateLFOWaveform,	  0, 1.0);

	///// SLEEP /////////////////////////////////////////////////////////////////////////////////
	m.setI(FeelingsManager::Feelings::Sleep, FeelingsManager::Inputs::Fsr,		  0, 1.0);
	m.setI(FeelingsManager::Feelings::Sleep, FeelingsManager::Inputs::Accel,	  0, 1.0);
	//m.setInputTarget(FeelingsManager::Inputs::Mic,	FeelingsManager::Feelings::Rage,	1, 1);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::Freq,	  0, 2.0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::LightHue,			 .6, 1.0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::LightSat,			 .2, 1.0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::LightLFOGain,		1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::LightLFOWaveform,	1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::VibrateStrengh,		  0, 2.0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::VibrateLFOGain,		  0,   0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::VibrateLFOWaveform,	1.0,   0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::SoundResp,	  1.0, 1.0);
	m.setO(FeelingsManager::Feelings::Sleep, FeelingsManager::Outputs::SoundVNR,	   .0, 1.0);
}

#endif