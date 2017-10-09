//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3 (Nano!)
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 132;
int R_START = 57;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

//J124-1 Sprit Ring
//J124-2 Saw
//J124-3 Jets
//J124-5 Trunk

int backgroundOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (backgroundOn){background();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {backgroundOn=1;}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){  //  trunk motor
    pd.adrLED1()->fadeIn("red",50);
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J126(2) ){ //  trunk motor
    pd.adrLED1()->fadeIn("red",50);
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J126(4) ){ 
    pd.adrLED1()->chase2Color("orange", "red",N_LEDS/8, 0, 1);
    trigger =1;
  }
//  if ( pd.pinState()->J126(5) ){ 
//    pd.adrLED1()->fadeIn("green",50);
//    pd.adrLED1()->fadeOut(50);
 //   trigger =1;
 // }
  if ( pd.pinState()->J126(8) ){ 
    pd.adrLED1()->chase2ColorFromPoint( R_START, "purple", "red", 10, 0);
    pd.adrLED1()->fadeOut(50);
    trigger=1;
  }
  if ( pd.pinState()->J126(13) ){ 
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "red", "yellow", 0);
    pd.adrLED1()->fadeOut(50);
    trigger=1;
  }
  if ( pd.pinState()->J126(14) ){ 
    pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 0, 1);
    trigger =1;
  }
  if ( pd.pinState()->J126(15) ){
//    pd.adrLED1()->color("yellow",100);
    pd.adrLED1()->spreadInFromPoint2Color(R_START, "yellow", "red", 0);
    pd.adrLED1()->fadeOut(50);
 //   delay(50); 
//    pd.adrLED1()->clear();
    pd.pinState()->update();
    trigger =1;
  }
  if ( pd.pinState()->J126(16)  and backgroundOn==0 ){
    pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 0, -1);
    trigger =1;
  }
 
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   backgroundOn = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void background() {
  int skip = 0; //if game has started, 
  if (!skip) {pd.adrLED1()->fadeIn("yellow", 100);}
  if (!skip) {pd.adrLED1()->fadeColor2Color("yellow", "red", 1000);}
  if (!skip) {pd.adrLED1()->fadeOut(1000);}
  if (pd.pinState()->any()) {skip =1;}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 10, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",N_LEDS/8, 10, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "purple",N_LEDS/8, 7, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("purple", "red",N_LEDS/8, 7, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 5, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",N_LEDS/8, 5, -1);}
}


