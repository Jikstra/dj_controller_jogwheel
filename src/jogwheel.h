#ifndef __JOGWHEEL_H_INCLUDED__
#define __JOGWHEEL_H_INCLUDED__

#include <Arduino.h>

extern int STATE_FOLLOWUP[4]; 

extern int COUNT_STATE_FOLLOWUP;

enum Direction { CW, CCW, UNSURE, INVALID, STAY };

char* state_to_string(int state);

int get_pin_state(int pin_ccw, int pin_cw);

#endif
