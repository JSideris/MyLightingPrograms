#line 1 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\libraries\\white-mode.h"
#include "programme.h"


class WhiteMode: public Programme{
	public:
		
		WhiteMode(): Programme(){
			
		}

		void tick(unsigned long dtU) override{
			// And set the light.
			for(int i = 0; i < NUM_LEDS; i++){
				int b = (fastSin[(i + millis() >> 3) % 256] >> 2) - 32;
				

				rChannel[i] = max(0, min(255, 223 + b));
				gChannel[i] = max(0, min(255, 168 + b));
				bChannel[i] = max(0, min(255, 118 + b));
				
			}
		}

		~WhiteMode(){
		}
};
