#ifndef LFO_H
#define LFO_H

#define MATH_PI 3.14159F

#define LFO_MIN  .10F //Hz
#define LFO_MAX 5.00F //Hz

#define LFO_DEBUG 0

class LFO {
public:
	float f = 1;
	float phase = 0; //[0:1]

	LFO(){}

	inline void setValue(float v, float step){
		f = LFO_MIN + v*(LFO_MAX-LFO_MIN);
		compute(step);
	}

	void compute(float step){
		phase += step*f;
		if(phase>1) phase -=1;
	}

	// 0 is Square
	// 1 is Cosine
	float computeForm(float beta, float mix) const {
		//raised cosine frequency domain function

		// convert 0->1 to 0->1->0
		float radPhase = phase*2;
		if(radPhase>1) radPhase = -radPhase+2;

		float r;
		if(radPhase < (1-beta)/2){
			r = 1;
		} else if(radPhase < (1+beta)/2){
			r = (1+cos(
				MATH_PI/beta * ( radPhase - (1-beta)/2 )
			))/2;
		} else {
			r = 0;
		}
		r = mix*r + (1-mix)*1;
		if(LFO_DEBUG){
			ComDebug("LFO:");
			ComDebug(f);ComDebug('\t');
			ComDebug(phase);ComDebug('\t');
			ComDebug(beta);ComDebug('\t');
			ComDebug(mix);ComDebug('\t');
			ComDebug(r);ComDebug('\n');
		}
		return r;
	}



};




#endif