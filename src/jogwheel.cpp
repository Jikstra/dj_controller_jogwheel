#include "jogwheel.h"

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

Direction process_pin_state(int pin_state, int* state, int* state_index) {
    if (*state == pin_state) return Direction::STAY;

    int next_state_index = mod((*state_index + 1), COUNT_STATE_FOLLOWUP);
    int prev_state_index = mod((*state_index - 1), COUNT_STATE_FOLLOWUP);
    //p("%s [%i %i %i] %s", state_to_string(*state), *state_index, next_state_index, prev_state_index, state_to_string(pin_state));

    if (STATE_FOLLOWUP[next_state_index] == pin_state) {
        //IFDEBUG(p("%s --> %s", state_to_string(*state), state_to_string(pin_state)));
        *state_index = next_state_index;
        *state = STATE_FOLLOWUP[next_state_index];
        
        if (*state == 0b00 || *state == 0b11) return Direction::CW;

    } else if (STATE_FOLLOWUP[prev_state_index] == pin_state) {
        //IFDEBUG(p("%s <-- %s", state_to_string(pin_state), state_to_string(*state)));
        *state_index = prev_state_index;
        *state = STATE_FOLLOWUP[prev_state_index];
        if (*state == 0b00 || *state == 0b11) return Direction::CCW;
    } else {
        return Direction::INVALID;
    }
    return Direction::UNSURE;
}
