#include "Arduino.h"

#define led_width 26
#define led_height 40
static const uint8_t ledBitsXBM[] PROGMEM = {
   0x00, 0xfc, 0x00, 0x00, 0x80, 0xff, 0x07, 0x00, 0xc0, 0x87, 0x0f, 0x00,
   0xe0, 0x00, 0x1c, 0x00, 0x70, 0x00, 0x38, 0x00, 0x38, 0x00, 0x70, 0x00,
   0x1c, 0x00, 0xe0, 0x00, 0x0c, 0x00, 0xc0, 0x00, 0x06, 0x00, 0x80, 0x01,
   0x06, 0x00, 0x80, 0x01, 0x06, 0x00, 0x80, 0x01, 0x07, 0x00, 0x80, 0x03,
   0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03,
   0x07, 0x00, 0x80, 0x03, 0x06, 0x00, 0x80, 0x01, 0xfe, 0xff, 0xff, 0x01,
   0xfe, 0xff, 0xff, 0x01, 0xcc, 0x30, 0xcc, 0x00, 0x98, 0x31, 0x66, 0x00,
   0x98, 0x31, 0x66, 0x00, 0x30, 0x33, 0x33, 0x00, 0x60, 0x33, 0x1b, 0x00,
   0x60, 0xb6, 0x19, 0x00, 0xc0, 0xb6, 0x0d, 0x00, 0xc0, 0xb6, 0x0d, 0x00,
   0x80, 0xff, 0x07, 0x00, 0x80, 0x00, 0x04, 0x00, 0x80, 0x00, 0x04, 0x00,
   0x80, 0xff, 0x07, 0x00, 0x80, 0x00, 0x04, 0x00, 0x80, 0x00, 0x04, 0x00,
   0x80, 0xff, 0x07, 0x00, 0x80, 0x01, 0x06, 0x00, 0x00, 0x01, 0x02, 0x00,
   0x00, 0xff, 0x03, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00,
   0x00, 0x78, 0x00, 0x00 };
