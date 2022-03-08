#line 1 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\libraries\\menu-settings.h"

#include "menu.h"

static String settingNames[] = {
	"My Programs",
	"Check WIFI",
	"Setup WIFI",
};

class MenuSettings: public Menu{
	public: 
		MenuSettings(){
			name = "[Settings]";
			cyclesLoop = true;
			activateInstantly = false;
			numbItems = 2;
		}

		String currentItemName() override{ 
			return settingNames[cursor]; 
		}
		void activateCurrentItem() override{}
		void saveSettings() override{}

		bool push() override{
			return true;
		}
		bool release() override{
			return true;
		}
};