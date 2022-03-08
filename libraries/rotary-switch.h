

#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6
#define DIR_NONE 0x0

#define DIR_CW 0x10
#define DIR_CCW 0x20

class RotarySwitch{
	public:
		bool pushBtnPushed = false;

		RotarySwitch(int clkPinP, int dtPinP, int swPinP, int vccPin, int gndPin){
			clkPin = clkPinP;
			dtPin = dtPinP;
			swPin = swPinP;

			pinMode(dtPin, INPUT_PULLUP);
			pinMode(clkPin, INPUT_PULLUP);
			pinMode(swPin, INPUT_PULLUP);
			pinMode(vccPin, OUTPUT);
			pinMode(gndPin, OUTPUT);
			digitalWrite(vccPin, HIGH);
			digitalWrite(gndPin, LOW);
		}

		unsigned char process(){

			// Grab state of input pins.
			unsigned char pinstate = (digitalRead(clkPin) << 1) | digitalRead(dtPin);

			// Determine new state from the pins and state table.
			state = ttable[state & 0xf][pinstate];

			// Return emit bits, ie the generated event.
			return state & 0x30;
		}

		bool readPushBtn(){
			if(pushBtnDebounce > 0){
				pushBtnDebounce--;
			}
			else{
				if(!digitalRead(swPin)){
					if(!pushBtnPushed){
						pushBtnPushed = true;
						pushBtnDebounce = 1;
						return true;
					}
				}
				else{
					pushBtnPushed = false;
				}

			}
			return false;
		}

	private: 
		int clkPin;
		int dtPin;
		int swPin;
		int state = R_START;
		int counter = 0;
		int pushBtnDebounce = 0;

		unsigned char ttable[7][4] = {
			// R_START
			{R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
			// R_CW_FINAL
			{R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
			// R_CW_BEGIN
			{R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
			// R_CW_NEXT
			{R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
			// R_CCW_BEGIN
			{R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
			// R_CCW_FINAL
			{R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
			// R_CCW_NEXT
			{R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
		};
};