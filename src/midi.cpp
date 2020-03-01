#include "midi.h"

void sendMIDI(int op, int channel, int control_number, int value) {
    Serial.write(op << 4 | channel);
    Serial.write(control_number);
    Serial.write(value);
}
