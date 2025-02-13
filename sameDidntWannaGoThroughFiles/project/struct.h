#ifndef STRUCTS_H
#define STRUCTS_H

extern union led {
  struct {
    uint8_t r, g, b;
  };
  uint32_t data;
} led_t;

#endif
