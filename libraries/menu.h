#ifndef MENU
#define MENU

#include <EEPROM.h>
#include "consts.h"

class Menu{
	public:
		String name = "TEST";
		int numbItems = 0;
		// String* items;
		int cursor;
		int saveSelection;
		bool activateInstantly = false;
		bool cyclesLoop = false;

		virtual String currentItemName(){}
		virtual void activateCurrentItem(){}
		virtual void saveSettings(){}

		virtual String cycleUp(){
			int oldCursor = cursor;
			if(cyclesLoop){
				cursor = (cursor + 1) % numbItems;
			}
			else{
				cursor = min(numbItems - 1, cursor + 1);
			}
			if(cursor != oldCursor && activateInstantly) activateCurrentItem();
			return currentItemName();
		}
		virtual String cycleDown(){
			int oldCursor = cursor;
			if(cyclesLoop){
				cursor = (cursor - 1 + numbItems) % numbItems;
			}
			else{
				cursor = max(0, cursor - 1);
			}
			if(cursor != oldCursor && activateInstantly) activateCurrentItem();
			return currentItemName();
		}
		virtual bool push(){
			return false;
		}
		virtual bool release(){
			return false;
		}

		Menu(){}
};



#endif