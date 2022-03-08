#line 1 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\libraries\\red-alert-mode.h"
#include "programme.h"


class RedAlertMode: public Programme{
	public:
		
		RedAlertMode(): Programme(){
			
		}

		void tick(unsigned long dtU) override{
			// And set the light.
			unsigned long m = millis()>>4;
			for(int i = 0; i < NUM_LEDS; i++){

				gChannel[i] = 0;
				bChannel[i] = 0;
				if((m + i) % 200 < 25 || (unsigned)(i + m + 100) % 200 < 25){
					rChannel[i] = 255;
				}
				else{
					rChannel[i] = fastSin[m % 256] >> 1;
				}
				
			}
		}

		~RedAlertMode(){
		}
};
