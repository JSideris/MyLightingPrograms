# 1 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino"




# 6 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 2
# 7 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 2


// #include "libraries/lcd.h"
# 11 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 2

# 13 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 2
# 14 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 2
# 15 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 2

# 17 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 2



int CLKPIN = 13; // Clk on encoder
int DTPIN = 12; // DT on encoder
int SVPIN = 11; // SV on encoder
RotarySwitch rotarySwitch(CLKPIN,DTPIN,SVPIN,10,9);

LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);
long backlightTimeout = 0;
const long backlightTimeoutMaxUs = 8333500l >> 1; // This is 100x higher than it should be. So wtf?
String lcdLine1;
String lcdLine2;

unsigned long oldT = 0;
int ticker = 0;

CRGB leds[300];

// Menus
// Todo: this could also be abstracted out in order to create sub menus.
static MenuBrightness brightnessMenu;
static MenuProgram programMenu;
static MenuSettings settingsMenu;
static Menu *allMenus[] = {
 &brightnessMenu, &programMenu, &settingsMenu
};
static int menuCursor = 0;
static int numbMenus = 3;

void setup(){
 // Random seed:
 unsigned long seed = micros();
 for(int i = 0; i <= 15; i++){
  seed += analogRead(i); // read the input pin
 }
 randomSeed(seed);




 FastLED.addLeds<WS2813, 2>(leds, 300);

 brightnessMenu.activateCurrentItem();

 programMenu.activateCurrentItem();

 lcd.init();
 lcd.setBacklight(0);
 lcd.clear();
 lcdLine1 = "";
 lcdLine2 = "";


 attachInterrupt((CLKPIN), digitalSwitchProcess, CHANGE);
 attachInterrupt((DTPIN), digitalSwitchProcess, CHANGE);
}

void cycleMenu(){
 cycleMenu((menuCursor + 1) % numbMenus);
}

void cycleMenu(int newIndex){
 menuCursor = newIndex;
 lcdLine1 = String("       ").substring(0, 8 - (allMenus[menuCursor]->name.length()>>1)) + allMenus[menuCursor]->name;
 lcdLine2 = "";
}

void digitalSwitchProcess(){
 int result = rotarySwitch.process();

 // lcd.clear();
 // lcd.setCursor(0, 0);
 // lcd.print(result);

 if(!result) return;

 if(rotarySwitch.pushBtnPushed){
  if(result == 0x10){
   cycleMenu();
  }
  else if(result == 0x20){
   cycleMenu((menuCursor - 1 + numbMenus) % numbMenus);
  }

 }
 else{
  lcdLine1 = allMenus[menuCursor]->name + ":";
  if(result == 0x10){
   lcdLine2 = allMenus[menuCursor]->cycleUp();
  }
  else if(result == 0x20){
   lcdLine2 = allMenus[menuCursor]->cycleDown();
  }
 }
}

void loop(){

 unsigned long t = micros();
 long dt = t - oldT;
 oldT = t;

 // lcdBufferLines = backlightTimeout;

 // Handle user input.

 // int nv = digitalRead(26);
 // if(nv){
 // };

 // LCD backlight:

 if(backlightTimeout > 0){
  backlightTimeout -= dt;
  if(backlightTimeout <= 0) {
   
# 133 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 3
  __asm__ __volatile__ ("cli" ::: "memory")
# 133 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino"
                ;
   // save settings
   allMenus[menuCursor]->saveSettings();
   // switch(menuCursor){
   // 	case 0:case 1:{
   // 		break;
   // 	}
   // 	case 2:{
   // 		break;
   // 	}
   // }
   backlightTimeout = 0;
   menuCursor = 0;
   lcd.setBacklight(0);
   lcd.clear();
   
# 148 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 3
  __asm__ __volatile__ ("sei" ::: "memory")
# 148 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino"
              ;
  }
 }

 if(lcdLine1.length()){
  
# 153 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 3
 __asm__ __volatile__ ("cli" ::: "memory")
# 153 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino"
               ;
  if(backlightTimeout <= 0) {
   lcd.setBacklight(1);
  }
  backlightTimeout = backlightTimeoutMaxUs;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(lcdLine1);
  lcdLine1 = "";
  lcd.setCursor(1,1);
  lcd.print(lcdLine2);
  
# 165 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 3
 __asm__ __volatile__ ("sei" ::: "memory")
# 165 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino"
             ;
 }

 if(rotarySwitch.readPushBtn()){
  if(!allMenus[menuCursor]->push()) cycleMenu();
 }

 // lcd.setCursor(0,0);
 // lcd.print(backlightTimeout);
 // lcd.print(" ");

 // // Handle lights: 

 // brightness = 255 - brightness;
 // brightness += dir;
 // if(brightness == 255 || brightness == 0) dir = -dir;
 // updateBrightness(brightness);

 currentProgram->tick(dt);

 for(int i = 0; i < 300; i++){
  //leds[i] = CRGB(255,255,255); 
  leds[i] = scaledRgb(currentProgram->rChannel[i],currentProgram->gChannel[i],currentProgram->bChannel[i]);
  // leds[i] = CRGB::White; 
 }


 leds[0] = (millis() / 1000) & 0b00001 ? CRGB(0,0,1) : CRGB::Black;


 
# 195 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 3
__asm__ __volatile__ ("cli" ::: "memory")
# 195 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino"
              ;
 FastLED.show();
 
# 197 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino" 3
__asm__ __volatile__ ("sei" ::: "memory")
# 197 "c:\\Users\\josh_\\OneDrive\\Desktop\\arduino-lights-2\\main.ino"
            ;

 // We want to update the strip at 60 fps if possible. For this we can use a delay of up to 16.667ms.
 delayMicroseconds(min(16667, 16667 - (micros() - oldT)));

 ticker++;
}

CRGB scaledRgb(uint8_t r, uint8_t g, uint8_t b){

 return CRGB(brightnessMatrix[r],brightnessMatrix[g],brightnessMatrix[b]);
}
