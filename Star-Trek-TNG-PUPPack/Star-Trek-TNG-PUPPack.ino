//Markus Kalkbrenner 2020
//Note to self:  Play more pinball!
//Interfaced for pinduino shield TNG (Mega Pro Embed!)
//Uses pinduino library WIP

#include "pinduino.h"

pinduino pd("TNG");

void setup() {
    Serial.begin(115200);
    pd.pin2Dmd()->forwardToPUP(pd.pupSerial());
}

void loop() {
    pd.pin2Dmd()->update();

    if (pd.switchMatrix()->getOnce(/* row */ 2, /* column */ 1, /* ignore for further reads for milli seconds */ 200)) {
        pd.pupSerial()->postEvent(PUP_TYPE_SWITCH, /* switch number */ 12);
        pd.switchMatrix()->reset();
    }
}
