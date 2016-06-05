#include "FastLED.h"

#include "lfo.h"

#define LED_NUM 5
#define LED_PIN 11


class Leds {
	CRGB buffer[LED_NUM];
	CRGB c;
	LFO const &lfo;

public:
	Leds(LFO const &l) :
		lfo(l) {
	}

	void init(){
		FastLED.addLeds<WS2812, LED_PIN, RGB>(buffer, LED_NUM);
		FastLED.setBrightness(255);
	}

	void draw(){
		FastLED.showColor( c );
	}

	void setValuesRaw(uint8_t r,uint8_t g,uint8_t b){
		c = CRGB(r, g, b);
		draw();
	}

	void setValue(float h, float s, float lfoGain, float lfoWaveform){
		float v = lfo.computeForm(lfoWaveform, lfoGain);
		c = CHSV( h*255 , s*255 , v*255 );
		draw();	
	}
};