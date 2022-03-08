#line 1 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\libraries\\color-mode.h"
#include "programme.h"


class ColorMode: public Programme{
	public:
		
		ColorMode(): Programme(){
			for(int i = 0; i < NUM_LEDS / 30; i++){
				addColor();
			}
		}

		void addColor(){
			int pi = random(NUM_LEDS);
			int l = 1 + random(10) + random(10);

			int r = pi % 3 == 0 ? 255 : random(255);
			int g = pi % 3 == 1 ? 255 : random(255);
			int b = pi % 3 == 2 ? 255 : random(255);
			for(int i = pi; i < pi+l; i++){
				int index = (i % NUM_LEDS);

				rChannel[index] = min(255, rChannel[index] + r);
				gChannel[index] = min(255, gChannel[index] + g);
				bChannel[index] = min(255, bChannel[index] + b);
			}
		}

		void tick(unsigned long dtU) override{
			
			if(!random(25)){
				// Add color.

				addColor();
			}

			for(int i = 0; i < NUM_LEDS; i++){
				if(i < NUM_LEDS - 1){
					int rx = rChannel[i] - rChannel[i+1];
					int gx = gChannel[i] - gChannel[i+1];
					int bx = bChannel[i] - bChannel[i+1];
					if(rx > 0 && random(rx) > 2){
						rChannel[i]--;
						rChannel[i+1]++;
					}
					if(rx < 0 && random(-rx) > 2){
						rChannel[i]++;
						rChannel[i+1]--;
					}
					if(gx > 0 && random(gx) > 4){
						gChannel[i]--;
						gChannel[i+1]++;
					}
					if(gx < 0 && random(-gx) > 4){
						gChannel[i]++;
						gChannel[i+1]--;
					}
					if(bx > 0 && random(bx) > 3){
						bChannel[i]--;
						bChannel[i+1]++;
					}
					if(bx < 0 && random(-bx) > 3){
						bChannel[i]++;
						bChannel[i+1]--;
					}
				}

				if(rChannel[i] && !random(4)) rChannel[i]--;
				if(gChannel[i] && !random(2)) gChannel[i]--;
				if(bChannel[i] && !random(3)) bChannel[i]--;
				
			}
		}

		~ColorMode(){
		}
};


// #include "programme.h"


// class ColorMode: public Programme{
// 	public:
		
// 		ColorMode(){
			

// 			for(int i = 0; i < NUM_LEDS; i++){

// 				rChannel[i] = 0;
// 				gChannel[i] = 0;
// 				bChannel[i] = 0;
			
// 			}
// 		}

// 		void tick(unsigned long dtU) override{
			
// 			if(!random(25)){
// 				// Add color.

// 				int pi = random(NUM_LEDS);
// 				int l = 1 + random(10) + random(10);

// 				int r = pi % 3 == 0 ? 255 : random(255);
// 				int g = pi % 3 == 1 ? 255 : random(255);
// 				int b = pi % 3 == 2 ? 255 : random(255);
// 				for(int i = pi; i < pi+l; i++){
// 					int index = (i % NUM_LEDS);

// 					rChannel[index] = min(255, rChannel[index] + r);
// 					gChannel[index] = min(255, gChannel[index] + g);
// 					bChannel[index] = min(255, bChannel[index] + b);
// 				}
// 			}

// 			for(int i = 0; i < NUM_LEDS; i++){
// 				if(random(rChannel[i]) > 50){
// 					if(i && rChannel[i - 1] < rChannel[i]) {
// 						rChannel[i - 1]++;
// 						rChannel[i]--;
// 					}
// 					if(i < NUM_LEDS - 1 && rChannel[i + 1] < rChannel[i]) {
// 						rChannel[i + 1]++;
// 						rChannel[i]--;
// 					}
// 				}
// 				else if(rChannel[i]) {
// 					if(random(rChannel[i]) > 30 || !random(4)) rChannel[i]--;
// 				}
// 				if(random(gChannel[i]) > 40){
// 					if(i && gChannel[i - 1] < gChannel[i]) {
// 						gChannel[i - 1]++;
// 						gChannel[i]--;
// 					}
// 					if(i < NUM_LEDS - 1 && gChannel[i + 1] < gChannel[i]) {
// 						gChannel[i + 1]++;
// 						gChannel[i]--;
// 					}
// 				}
// 				else if(gChannel[i]) {
// 					if(random(gChannel[i]) > 30 || !random(4)) gChannel[i]--;
// 				}
// 				if(random(bChannel[i]) > 30){
// 					if(i && bChannel[i - 1] < bChannel[i]) {
// 						bChannel[i - 1]++;
// 						bChannel[i]--;
// 					}
// 					if(i < NUM_LEDS - 1 && bChannel[i + 1] < bChannel[i]) {
// 						bChannel[i + 1]++;
// 						bChannel[i]--;
// 					}
// 				}
// 				else if(bChannel[i]) {
// 					if(random(bChannel[i]) > 30 || !random(4)) bChannel[i]--;
// 				}
				
// 			}
// 		}

// 		~ColorMode(){
// 		}
// };
