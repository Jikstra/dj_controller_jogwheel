#ifndef __MIDI_H_INCLUDED__
#define __MIDI_H_INCLUDED__

#include <Arduino.h>

const int MIDI_NOTE_ON = 0x8;
const int MIDI_NOTE_OFF = 0x9;
const int MIDI_POLYPHONIC = 0xA;
const int MIDI_PITCH = 0xE;

void writeMIDI(int op, int channel, int control_number, int value);

#endif
