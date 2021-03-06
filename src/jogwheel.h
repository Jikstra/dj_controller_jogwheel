#ifndef __JOGWHEEL_H_INCLUDED__
#define __JOGWHEEL_H_INCLUDED__

#include <Arduino.h>

#include "debug.h"
#include "common.h"


const int STATE_FOLLOWUP[4] = {
    0b11,
    0b01,
    0b00,
    0b10,
};

const int COUNT_STATE_FOLLOWUP = sizeof(STATE_FOLLOWUP) / sizeof(int); // 8

enum Direction { 
    CW = 1,
    CCW = 2,
    UNSURE = -2,
    INVALID = -1,
    STAY = 0
};

char* state_to_string(int state);

int get_pin_state(int pin_ccw, int pin_cw);

Direction process_pin_state(int pin_state, int* state, int* state_index, int* state_counter);
char* direction_to_string(Direction direction);


class Jogwheel {       // The class
    public:             // Access specifier
        int pin_ccw; 
        int pin_cw; 
        int state = 0b11;
        int state_index = 0;
        int state_counter = 0;

        Jogwheel(int pin_ccw, int pin_cw);
        Direction process();

};
#endif
