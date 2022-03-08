#line 1 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\libraries\\big-fire-mode.h"
#include "programme.h"


class BigFireMode: public Programme{
	public:

		int flameTarget[NUM_LEDS];
		
		BigFireMode(): Programme(){
			
		}

		void tick(unsigned long dtU) override{
			// And set the light.
			unsigned int t = millis() >> 3;
			int baseline = min(256, (fastSin[(t)%256] + fastSin[(t*2)%256] + fastSin[(t*3)%256] + fastSin[(t*5)%256] + fastSin[(t*7)%256] + fastSin[(t*11)%256] + fastSin[(t*13)%256] + fastSin[(t*17)%256])>>3);
			for(int i = 0; i < NUM_LEDS; i++){
				//int b = (fastSin[(i + millis() >> 3) % 256] >> 2) - 32;
				// if(!random(5)) flameTarget[i] = (fastSin[(i + millis()>>3)%256] * random(60)) >> 8;
				// if(!random(15)) flameTarget[i] = random(20);
				// else if(!random(16)) flameTarget[i] = 40 + random(20);
				// else if(!random(20)) flameTarget[i] = random(60);
				if(!random(10)) {
					if(baseline > 127){
						flameTarget[i] = (40 + random(20));
						flameTarget[i] = 60;
					}
					else{
						flameTarget[i] = (random(20));
						flameTarget[i] = 0;
					}
				}

				rChannel[i] = max(0, min(255, 255));
				//gChannel[i] = max(0, min(255, ));
				gChannel[i] += (flameTarget[i] - gChannel[i]) >> 2;
				// if(flameTarget[i] > gChannel[i]) gChannel[i]++;
				// else if(flameTarget[i] < gChannel[i]) gChannel[i]--;
				bChannel[i] = max(0, min(255, 0));
				
			}
		}

		~BigFireMode(){
		}
};
