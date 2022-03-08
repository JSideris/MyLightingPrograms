#line 1 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\libraries\\menu-program.h"

#include "menu.h"
#include "consts.h"
#include "big-fire-mode.h"
#include "torch-mode.h"
#include "white-mode.h"
#include "red-alert-mode.h"
#include "color-mode.h"
#include "snakes-mode.h"

Programme* currentProgram;
static String programNames[] = {
	"Color Splash", 
	"Fire", 
	"Red Alert", 
	"Snakes", 
	"Torches (Fire)", 
	"Torches (Magic)", 
	"White"
};
static void setSnakesMode(){currentProgram = new SnakesMode();}
static void setBigFireMode(){currentProgram = new BigFireMode();}
static void setColorMode(){currentProgram = new ColorMode();}
static void setRedAlertMode(){currentProgram = new RedAlertMode();}
static void setTorchMode(){currentProgram = new TorchMode(false);}
static void setMagicTorchMode(){currentProgram = new TorchMode(true);}
static void setWhiteMode(){currentProgram = new WhiteMode();}
static void (*programs[])() = {
	setColorMode, 
	setBigFireMode, 
	setRedAlertMode, 
	setSnakesMode, 
	setTorchMode, 
	setMagicTorchMode, 
	setWhiteMode
};

class MenuProgram: public Menu{
	public: 

		MenuProgram(){
			numbItems = 6;
			name = "[Programs]";
			cursor = min(numbItems - 1, EEPROM.read(LAST_PROGRAM_ADDR));
			cyclesLoop = true;
			activateInstantly = true;
		}

		String currentItemName() override{ 
			return programNames[cursor]; 
		}
		void activateCurrentItem() override{
			if(currentProgram)
			{
				delete currentProgram;
			}
			(*programs[cursor])();
		}

		void saveSettings() override{
			EEPROM.write(LAST_PROGRAM_ADDR, (uint8_t) cursor);
		}
};