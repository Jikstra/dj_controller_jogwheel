#include "main.h"

const int PIN_PHOTO_CCW = 2;
const int PIN_PHOTO_CW = 3;

int STATE_FOLLOWUP[] = {
    0b11,
    0b01,
    0b00,
    0b10,
};

int COUNT_STATE_FOLLOWUP = sizeof(STATE_FOLLOWUP) / sizeof(int); // 8

enum Direction { CW, CCW, UNSURE, INVALID, STAY };

int state = 0b11;
int state_index = 0;

char* state_to_string(int state) {
    if      (state == 0b00) { return (char*) "0b00"; }
    else if (state == 0b01) { return (char*) "0b01"; }
    else if (state == 0b10) { return (char*) "0b10"; }
    else if (state == 0b11) { return (char*) "0b11"; }
    else                    { return (char*) "0bERR"; }
}

int get_pin_state() {
    int left = digitalRead(PIN_PHOTO_CCW);
    int right = digitalRead(PIN_PHOTO_CW);

    int pin_state = left << 1 | right << 0;
    return pin_state;
}

int mod (int a, int b)
{
   if(b < 0) return -mod(-a, -b);   
   
   int ret = a % b;
   if(ret < 0) ret+=b;
   
   return ret;
}

Direction process_pin_state(int pin_state, int* state, int* state_index) {
if (*state == pin_state) return Direction::STAY;

    int next_state_index = mod((*state_index + 1), COUNT_STATE_FOLLOWUP);
    int prev_state_index = mod((*state_index - 1), COUNT_STATE_FOLLOWUP);
    //p("%s [%i %i %i] %s", state_to_string(*state), *state_index, next_state_index, prev_state_index, state_to_string(pin_state));

    if (STATE_FOLLOWUP[next_state_index] == pin_state) {
        p("%s --> %s", state_to_string(*state), state_to_string(pin_state));
        *state_index = next_state_index;
        *state = STATE_FOLLOWUP[next_state_index];
        
        if (*state == 0b00 || *state == 0b11) return Direction::CW;

    } else if (STATE_FOLLOWUP[prev_state_index] == pin_state) {
        p("%s <-- %s", state_to_string(pin_state), state_to_string(*state));
        *state_index = prev_state_index;
        *state = STATE_FOLLOWUP[prev_state_index];
        if (*state == 0b00 || *state == 0b11) return Direction::CCW;
    } else {
        return Direction::INVALID;
    }
    return Direction::UNSURE;
}


void setup()
{
    Serial.begin(115200);
}


unsigned int counter = 0;
void loop()
{ 
    int pin_state = get_pin_state();
    Direction direction = process_pin_state(pin_state, &state, &state_index);
    if (direction == Direction::CW) {
        counter++;
        p("CW  %i", counter);
    } else if (direction == Direction::CCW) {
        counter--;
        p("CCW %i", counter);
    }
}

