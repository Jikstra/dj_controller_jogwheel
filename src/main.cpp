#include "main.h"

const int PIN_PHOTO_CCW = 2;
const int PIN_PHOTO_CW = 3;
const int PIN_BUTTON_CUE = 4;




void setup()
{
    Serial.begin(115200);

    pinMode(PIN_BUTTON_CUE, INPUT_PULLUP);
}


Jogwheel jogwheel(PIN_PHOTO_CCW, PIN_PHOTO_CW);
IFDEBUG(int debug_jogwheel_counter = 0);
void process_jogwheel() {
    Direction direction = jogwheel.process();

    if (direction <= 0) return; 

    IFDEBUG(
        p("[JOGWHEEL] DIRECTION: %s", direction_to_string(direction));
        debug_jogwheel_counter = mod(
            direction == Direction::CW ?
                debug_jogwheel_counter + 1 :
                debug_jogwheel_counter - 1,
            120
        );
        p("[JOGWHEEL] COUNTER: %i", debug_jogwheel_counter)
    );

    IFNDEBUG(sendMIDI(MIDI_PITCH, 0, 1, direction == Direction::CW ? 1 : 0));
}

int button_state = 0;
void process_button_cue() {
    const int value = digitalRead(PIN_BUTTON_CUE);

    if (value == 1) return;

    IFDEBUG(p("BUTTON CUE"));

    IFNDEBUG(sendMIDI(MIDI_NOTE_ON, 0, 2, 0));
}


void loop() {
    process_jogwheel();
    process_button_cue();
}

