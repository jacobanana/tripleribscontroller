#include <Arduino.h>
#include <Bounce2.h>
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

#define SWITCH1_PIN 2
#define SWITCH2_PIN 3
#define SWITCH3_PIN 0
#define MIDI_TX_PIN 1
#define SWITCH_INTERVAL 10
#define INTERNAL_LED 13

Bounce2::Button switch1;
Bounce2::Button switch2;
Bounce2::Button switch3;
bool ledState = 1;

void setup() {
    MIDI.begin(MIDI_CHANNEL_OMNI);
    pinMode(INTERNAL_LED, OUTPUT);
    digitalWrite(INTERNAL_LED, ledState);

    switch1.attach(SWITCH1_PIN, INPUT_PULLUP);
    switch1.interval(SWITCH_INTERVAL);
    
    switch2.attach(SWITCH2_PIN, INPUT_PULLUP);
    switch2.interval(SWITCH_INTERVAL);

    switch3.attach(SWITCH3_PIN, INPUT_PULLUP);
    switch3.interval(SWITCH_INTERVAL);
}

void sendRealTimeMidi(midi::MidiType message){
    // send real time messages to both ports
    MIDI.sendRealTime(message);
    usbMIDI.sendRealTime(message);
    ledState = !ledState;
    digitalWrite(INTERNAL_LED, ledState);
}

void loop() {
    switch1.update();
    switch2.update();
    switch3.update();
    
    if (switch1.fell()) {
        sendRealTimeMidi(midi::Start);
    }
    else if (switch2.fell()) {
        sendRealTimeMidi(midi::Stop);
    } 
    else if (switch3.fell()) {
        sendRealTimeMidi(midi::Continue);
    } 
}
