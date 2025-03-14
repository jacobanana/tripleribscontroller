#include <Arduino.h>
#include <Bounce2.h>

#define SWITCH1_PIN 2
#define SWITCH2_PIN 3
#define SWITCH3_PIN 0
#define MIDI_TX_PIN 1
#define SWITCH_INTERVAL 10

Bounce2::Button switch1;
Bounce2::Button switch2;
Bounce2::Button switch3;

void setup() {
    switch1.attach(SWITCH1_PIN, INPUT_PULLUP);
    switch1.interval(SWITCH_INTERVAL);
    
    switch2.attach(SWITCH2_PIN, INPUT_PULLUP);
    switch2.interval(SWITCH_INTERVAL);

    switch3.attach(SWITCH3_PIN, INPUT_PULLUP);
    switch3.interval(SWITCH_INTERVAL);
}

void loop() {
    switch1.update();
    switch2.update();
    switch3.update();
    
    if (switch1.fell()) {
        usbMIDI.sendRealTime(usbMIDI.Start);
    }
    else if (switch2.fell()) {
        usbMIDI.sendRealTime(usbMIDI.Stop);
    } 
    else if (switch3.fell()) {
        usbMIDI.sendRealTime(usbMIDI.Continue);
    } 
}
