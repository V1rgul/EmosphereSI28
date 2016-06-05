#ifndef FEELINGS_H
#define FEELINGS_H

#include "com.h"

#define FEELINGS_DEBUG 0

typedef uint8_t neuronInputSize_t;

class FeelingsManager {
public:
	//enum class because I love static_cast<>() ^^"
	enum class Inputs {
		Fsr, Accel, /*Mic,*/ SIZE
	};
	enum class Feelings {
		Rage, Fear, Joy, Love, /*Sad,*/ Sleep, SIZE
	};
	enum class Outputs {
		Freq,
		LightHue, LightSat, LightLFOGain, LightLFOWaveform,
		VibrateStrengh, VibrateLFOGain, VibrateLFOWaveform,
		SoundResp, SoundVNR,
		SIZE
	};

protected: /////////////////////////////////////////////////////////
	template<neuronInputSize_t NeuronInputNumber>
	class Neuron {
	protected:
		float target[NeuronInputNumber] = {};
		float coeff[NeuronInputNumber] = {}; //coeffs at 0
	public:
		inline void setTarget(neuronInputSize_t input, float t, float c){
			target[input] = t;
			coeff[input] = c;
		}
	};
	template<neuronInputSize_t NeuronInputNumber>
	class NeuronFeeling : public Neuron<NeuronInputNumber> {
	protected:
		static constexpr float slope=0.2, window=0.1; //only half side
	public:
		float compute(float in[], float fG){
			float sum = 0, sumCoeffs = 0;
			for(neuronInputSize_t i=0; i<NeuronInputNumber; i++){
				//this-> is needed because apparently target & coeff arent dependant names. See Two-phase name lookup
				float dist = abs(in[i]-this->target[i])-window;
				//there was a warning in macro abs when dist wasnt in a separate variable :o
				sum += (1-constrain( dist/slope, 0,1)) * this->coeff[i];
				sumCoeffs += this->coeff[i];
				if(FEELINGS_DEBUG){
					ComDebug("NF[");ComDebug(i);ComDebug("]");
					ComDebug(dist);ComDebug('\t');
					ComDebug(sum);ComDebug('\n');
				}
			}
			if(sumCoeffs==0) return 0; //prevent division by 0
			else             return pow(sum/sumCoeffs, fG);
		}
	};
	template<neuronInputSize_t NeuronInputNumber>
	class NeuronOutput : public Neuron<NeuronInputNumber> {
	public:
		float compute(float in[], float specG){
			float sum = 0, sumCoeffs = 0;
			for(neuronInputSize_t i=0; i<NeuronInputNumber; i++){
				float inG = pow(in[i],specG);
				sum       += inG * this->coeff[i] * this->target[i];
				sumCoeffs += inG * this->coeff[i];
				if(FEELINGS_DEBUG){
					ComDebug("NO[");ComDebug(i);ComDebug("] ");
					ComDebug("in_");ComDebug(in[i]);ComDebug('\t');
					ComDebug("inG_");ComDebug(inG);ComDebug('\t');
					ComDebug("t_");ComDebug(this->target[i]);ComDebug('\t');
					ComDebug("s+_");ComDebug(inG * this->coeff[i] * this->target[i]);ComDebug('\t');
					ComDebug("s_");ComDebug(sum);ComDebug('\t');
					ComDebug("sc+_");ComDebug(inG * this->coeff[i]);ComDebug('\t');
					ComDebug("sc_");ComDebug(sumCoeffs);ComDebug('\n');
				}
			}
			if(sumCoeffs==0) return 0; //prevent division by 0
			else             return sum/sumCoeffs;
		}
	};

	///////////////////////////////////////////////////////////////

protected:
	float inputValues[static_cast<neuronInputSize_t>(Inputs::SIZE)];
	float feelingsGamma = 1;
	NeuronFeeling<static_cast<neuronInputSize_t>(Inputs::SIZE)> feelings[static_cast<neuronInputSize_t>(Feelings::SIZE)];
	float feelingValues[static_cast<neuronInputSize_t>(Feelings::SIZE)];
	float specificGamma[static_cast<neuronInputSize_t>(Outputs::SIZE)];
	NeuronOutput<static_cast<neuronInputSize_t>(Feelings::SIZE)> outputs[static_cast<neuronInputSize_t>(Outputs::SIZE)];
	float outputValues[static_cast<neuronInputSize_t>(Outputs::SIZE)];
public:
	FeelingsManager(){
		for(neuronInputSize_t n=0; n<static_cast<neuronInputSize_t>(Outputs::SIZE); n++){
			specificGamma[n] = 1;
		}
	}

	//set INput Target & coeff
	void setI(Feelings feeling, Inputs input, float target, float coeff){
		target = constrain(target, 0, 1);
		feelings[static_cast<neuronInputSize_t>(feeling)].setTarget(static_cast<neuronInputSize_t>(input), target, coeff);
	}

	//set OUTput Target & coeff
	void setO(Feelings feeling, Outputs output, float target, float coeff){
		target = constrain(target, 0, 1);
		outputs[static_cast<neuronInputSize_t>(output)].setTarget(static_cast<neuronInputSize_t>(feeling), target, coeff);
	}

	//set global Feelings Gamma
	void setFeelingsGamma(float g){
		feelingsGamma = g;
	}

	//set specific output gamma (helps differentiating Feelings)
	void setSpecificGamma(Outputs output, float g){
		specificGamma[static_cast<neuronInputSize_t>(output)] = g;
	}

	inline void setInput(Inputs input, float v){ inputValues[static_cast<neuronInputSize_t>(input)] = v; } //inline?

	void compute(){
		for(neuronInputSize_t n=0; n<static_cast<neuronInputSize_t>(Feelings::SIZE); n++){
			feelingValues[n] = feelings[n].compute(inputValues, feelingsGamma);
		}
		for(neuronInputSize_t n=0; n<static_cast<neuronInputSize_t>(Outputs::SIZE); n++){
			outputValues[n] = outputs[n].compute(feelingValues, specificGamma[n]);
		}
	};
	
	inline float getOutput(Outputs output) const {
		return outputValues[static_cast<neuronInputSize_t>(output)];
	}

	void debug() const {
		ComDebug("Inputs : ");
		for(neuronInputSize_t i=0; i<static_cast<neuronInputSize_t>(Inputs::SIZE); i++){
			ComDebug(inputValues[i]);
			ComDebug('\t');
		}
		ComDebug('\n');
		ComDebug("Feelings: ");
		for(neuronInputSize_t i=0; i<static_cast<neuronInputSize_t>(Feelings::SIZE); i++){
			ComDebug(feelingValues[i]);
			ComDebug('\t');
		}
		ComDebug('\n');
		ComDebug("Outputs : ");
		for(neuronInputSize_t i=0; i<static_cast<neuronInputSize_t>(Outputs::SIZE); i++){
			ComDebug(outputValues[i]);
			ComDebug('\t');
		}
		ComDebug('\n');
	}

};



#endif