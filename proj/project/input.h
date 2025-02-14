#ifndef INPUT_H
#define INPUT_H

#include <inttypes.h>

bool red_knob_pressed(uint8_t *mem_base);
bool blue_pressed(uint8_t *mem_base);
uint8_t red_knob(uint8_t *mem_base);

#endif