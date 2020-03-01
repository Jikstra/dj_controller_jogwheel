#include "main.h"

const int PIN_PHOTO_CCW = 2;
const int PIN_PHOTO_CW = 3;
const int PIN_BUTTON_CUE = 4;


int state = 0b11;
int state_index = 0;


void setup()
{
    Serial.begin(115200);

    pinMode(PIN_BUTTON_CUE, INPUT_PULLUP);
}
    
void process_jogwheel() {
    int pin_state = get_pin_state(PIN_PHOTO_CCW, PIN_PHOTO_CW);
    Direction direction = process_pin_state(pin_state, &state, &state_index);

    if (direction <= 0) return; 

    IFDEBUG(p("%s %i", (direction == Direction::CW ? "CW" : "CCW")));

    IFNDEBUG(writeMIDI(MIDI_PITCH, 0, 1, direction == Direction::CW ? 1 : 0));
}

int button_state = 0;
void process_button_cue() {
    const int value = digitalRead(PIN_BUTTON_CUE);

    if (value == 1) return;

    IFDEBUG(p("BUTTON CUE"));

    IFNDEBUG(writeMIDI(MIDI_NOTE_ON, 0, 2, 0));
}

void loop() {
    process_jogwheel();
    process_button_cue();
}

