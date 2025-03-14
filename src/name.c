#include <usb_names.h>

#define MIDI_NAME {'R','i','b','s','C','o','n','t','r','o','l'}
#define MIDI_NAME_LEN 11

struct usb_string_descriptor_struct usb_string_product_name = {
    2 + MIDI_NAME_LEN * 2,
    3,
    MIDI_NAME
};
