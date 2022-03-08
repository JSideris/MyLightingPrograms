
#include "menu.h"

static uint8_t userBrightnessMap[12] = {0, 3, 10, 23, 41, 64, 92, 125, 163, 206, 255};
uint8_t brightnessMatrix[256];

class MenuBrightness: public Menu{
	public: 

		int lastBrightnessLevelBeforeShutoff = 8;
		bool restoreReady = false;

		MenuBrightness() : Menu(){
			name = "[Brightness]";
			numbItems = 11;
			activateInstantly = true;
			lastBrightnessLevelBeforeShutoff = cursor = min(10, EEPROM.read(LAST_BRIGHTNESS_ADDR));
		}

		void saveSettings() override{
			EEPROM.write(LAST_BRIGHTNESS_ADDR, (uint8_t) cursor);
			if(cursor){
				lastBrightnessLevelBeforeShutoff = cursor;
			}
			else{
				restoreReady = true;
			}
		}

		String currentItemName() override{
			if(cursor > 0) {
				return String(cursor) + "/10";
			}
			return "OFF";
		}

		void activateCurrentItem() override{
			int brightness = userBrightnessMap[cursor];
	
			// lcdBufferLines.
			for(long i = 0; i < 256; i++){
				brightnessMatrix[i] = ((long)brightness * i) >> 8l;
			}
		}

		String cycleUp() override{
			if(restoreReady && !cursor && lastBrightnessLevelBeforeShutoff){
				restoreReady = false;
				cursor = lastBrightnessLevelBeforeShutoff;
				if(activateInstantly) activateCurrentItem();
					return currentItemName();
			}
			else
				return Menu::cycleUp();
		}
		String cycleDown() override{
			restoreReady = false;
			return Menu::cycleDown();
		}
};
