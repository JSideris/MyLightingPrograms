#include "programme.h"

class SnakesMode: public Programme{
	public:

		int rArray[20];
		int gArray[20];
		int bArray[20];

		int speedArray[20];
		int startArray[20];
		int endArray[20];
		bool setArray[20];
		int activeSnakes = 0;
		
		SnakesMode(): Programme(){
			for(int i = 0; i < 20; i++)	{
				rArray[i] = 0;
				gArray[i] = 0;
				bArray[i] = 0;

				speedArray[i] = 0;
				startArray[i] = 0;
				endArray[i] = 0;
				setArray[i] = false;

				if(!random(3)){
					create(i);
				}
			}

			
		}

		void tick(unsigned long dtU) override{
			
			// if(!random(25)){
			// 	// Add color.

			// 	int pi = random(NUM_LEDS);
			// 	int l = 1 + random(10) + random(10);

			// 	int r = pi % 3 == 0 ? 255 : random(255);
			// 	int g = pi % 3 == 1 ? 255 : random(255);
			// 	int b = pi % 3 == 2 ? 255 : random(255);
			// 	for(int i = pi; i < pi+l; i++){
			// 		int index = (i % NUM_LEDS);

			// 		rChannel[index] = min(255, rChannel[index] + r);
			// 		gChannel[index] = min(255, gChannel[index] + g);
			// 		bChannel[index] = min(255, bChannel[index] + b);
			// 	}
			// }

			for(int i = 0; i < NUM_LEDS; i++){
				rChannel[i] = max(0, rChannel[i] - (20));
				gChannel[i] = max(0, gChannel[i] - (20));
				bChannel[i] = max(0, bChannel[i] - (20));
			}

			for(int i = 0; i < 20; i++){
				setArray[i] = false;
			}
			for(int i = 0; i < 20; i++){
				if(speedArray[i]){
					for(int j = startArray[i]; j < endArray[i]; j++){
						if(j < NUM_LEDS && j >= 0){
							if(setArray[i]){
								// rChannel[j] = min(255, rChannel[j] + rArray[i]);
								// gChannel[j] = min(255, gChannel[j] + gArray[i]);
								// bChannel[j] = min(255, bChannel[j] + bArray[i]);
								
								rChannel[j] = max(rChannel[j], rArray[i]);
								gChannel[j] = max(gChannel[j], gArray[i]);
								bChannel[j] = max(bChannel[j], bArray[i]);
							}
							else{
								rChannel[j] = min(255, rArray[i]);
								gChannel[j] = min(255, gArray[i]);
								bChannel[j] = min(255, bArray[i]);
							}
							setArray[i] = true;
						}
					}

					startArray[i] += speedArray[i];
					endArray[i] += speedArray[i];

					if(endArray[i] < 0 || startArray[i] >= NUM_LEDS){
						speedArray[i] = 0;
						activeSnakes--;
					}
				}
				else if(!activeSnakes || !random(300 + 50 * activeSnakes + fastSin[(millis() >> 5) % 256] * 4)){
					create(i);
				}
			}
		}

		void create(int i){
			activeSnakes++;
			int rnd = random(3);
			rArray[i] = rnd % 3 == 0 ? 255 : random(255);
			gArray[i] = rnd % 3 == 1 ? 255 : random(255);
			bArray[i] = rnd % 3 == 2 ? 255 : random(255);
			int absSpeed = 1 + random(2) + random(2) + random(2);
			if(!random(2)) {
				speedArray[i] = -absSpeed;

				startArray[i] = NUM_LEDS;
				endArray[i] = NUM_LEDS + max(2, absSpeed);

			}
			else{
				speedArray[i] = absSpeed;

				startArray[i] = - max(2, absSpeed);
				endArray[i] = 0;
			}
		}

		~SnakesMode(){
		}
};
