//Markus Kalkbrenner 2020
//Note to self:  Play more pinball!
//Interfaced for pinduino shield TNG (Mega Pro Embed!)
//Uses pinduino library WIP

#include <pinduino.h>

pinduino pd("TNG");

void setup() {
    Serial.begin(115200);
    pd.pin2Dmd()->forward(pd.pupSerial);
}

void loop() {
    pd.pin2Dmd()->update();
}
