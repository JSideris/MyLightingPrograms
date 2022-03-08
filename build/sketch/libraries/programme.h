#line 1 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\libraries\\programme.h"
#ifndef PROGRAMME
#define PROGRAMME

#include "consts.h"

class Programme 
{
	public:
		// CRGB rawLeds[NUM_LEDS];
		uint8_t rChannel[NUM_LEDS];
		uint8_t gChannel[NUM_LEDS];
		uint8_t bChannel[NUM_LEDS];
		
		// Quick math ops:
		int fastSin[256];

		Programme(){
			for(int i = 0; i < 256; i++){
				fastSin[i] = 127.5 * sin((PI * 2.0 * i ) / 256.0) + 127.5;
			}

			for(int i = 0; i < NUM_LEDS; i++){

				rChannel[i] = 0;
				gChannel[i] = 0;
				bChannel[i] = 0;
			
			}
		}

		~Programme(){
		}

		virtual void tick(unsigned long dtU){ }
		
		// Probability per minute of something happening.
		bool prob(double ppms, unsigned int elapsedUs){
			// return ppu < random(elapsedUs);
			return !random(100);
			//return random(100000000) < (1.0 - pow(1.0 - ppms, 0.001 * elapsedUs)) * 100000000;
		}

	private:
		double le = log(2.71828);
};

#endif