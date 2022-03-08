#include "programme.h"


class TorchMode: public Programme{
	public:
		static int fireWidth;
		static int fireSpacing;
		bool magicMode;
		// unsigned int flame[NUM_LEDS];

		TorchMode(bool magicMode): Programme(){
			this->magicMode = magicMode;
		}

		void tick(unsigned long dtU) override{
			// And set the light.
			for(int i = 0; i < NUM_LEDS; i += fireSpacing){
				for(int j = 0; j < fireSpacing && j+i < NUM_LEDS; j++){
					int k = j+i;
					if(j > fireWidth){
						rChannel[k] = gChannel[k] = bChannel[k] = 0;
						continue;
					}
					

					if(!magicMode){
						rChannel[k] = 128 + (fastSin[ ((millis()>>3 )  + k ) % 256] >> 1);
						gChannel[k] = max(0, min(rChannel[k] - 30, (fastSin[ ((millis()>>6 ) + i * 1000 + j ) % 256] >> 3) + 2 ));
						bChannel[k] = 1;
					}
					else{
						// rChannel[k] = 1;
						rChannel[k] = max(0, min(255, (fastSin[ ((millis()>>7 ) + i * 2000 + j ) % 256] >> 3) + 2 ));
						gChannel[k] = max(0, min(255, (fastSin[ ((millis()>>6 ) + i * 1000 + j ) % 256] >> 3) + 2 ));
						bChannel[k] = 64 + (fastSin[ ((millis()>>3 )  + k ) % 256] >> 1);
					}

				}
			}
		}

		~TorchMode(){
		}
};


int TorchMode::fireWidth = 4;
int TorchMode::fireSpacing = 22;