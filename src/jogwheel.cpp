#include "jogwheel.h"

int STATE_FOLLOWUP[4] = {
    0b11,
    0b01,
    0b00,
    0b10,
};

int COUNT_STATE_FOLLOWUP = sizeof(STATE_FOLLOWUP) / sizeof(int); // 8

char* state_to_string(int state) {
    if      (state == 0b00) { return (char*) "0b00"; }
    else if (state == 0b01) { return (char*) "0b01"; }
    else if (state == 0b10) { return (char*) "0b10"; }
    else if (state == 0b11) { return (char*) "0b11"; }
    else                    { return (char*) "0bERR"; }
}

int get_pin_state(int pin_ccw, int pin_cw) {
    int left = digitalRead(pin_ccw);
    int right = digitalRead(pin_cw);

    int pin_state = left << 1 | right << 0;
    return pin_state;
}
