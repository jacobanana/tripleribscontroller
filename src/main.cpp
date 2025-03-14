#include <Arduino.h>
#include <Bounce2.h>
// #include <usbMIDI.h>

#define SWITCH1_PIN 2
#define SWITCH2_PIN 3
#define SWITCH3_PIN 0
#define MIDI_TX_PIN 1
#define MIDI_CHANNEL 1
#define CC_NUMBER 20
#define SWITCH_INTERVAL 10

Bounce2::Button switch1;
Bounce2::Button switch2;
Bounce2::Button switch3;
uint8_t lastValue = 255;

void setup() {
    switch1.attach(SWITCH1_PIN, INPUT_PULLUP);
    switch1.interval(SWITCH_INTERVAL);
    
    switch2.attach(SWITCH2_PIN, INPUT_PULLUP);
    switch2.interval(SWITCH_INTERVAL);

    switch3.attach(SWITCH3_PIN, INPUT_PULLUP);
    switch3.interval(SWITCH_INTERVAL);

}

void sendMIDI(uint8_t value) {
    usbMIDI.sendControlChange(CC_NUMBER, value, MIDI_CHANNEL);
}

void loop() {
    switch1.update();
    switch2.update();
    switch3.update();
    

    uint8_t value = 0;

    if (switch1.fell()) {
        usbMIDI.sendRealTime(usbMIDI.Start);
        value = 32; // S1
    }
    else if (switch2.fell()) {
        value = 64; // S2
        usbMIDI.sendRealTime(usbMIDI.Stop);
    } 
    else if (switch3.fell()) {
        value = 127; // S3
        usbMIDI.sendRealTime(usbMIDI.Continue);

    } 
    // else if (switch1.rose() || switch2.rose() || switch3.rose()){
    //     lastValue = 0;
    // }
    
    // if (value != lastValue && value != 0) {
    //     sendMIDI(value);
    //     lastValue = value;
    // }

    // usbMIDI.read(); // Process incoming USB MIDI messages
}
