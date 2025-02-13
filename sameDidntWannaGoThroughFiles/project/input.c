#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <inttypes.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"

#define RED 0b100
#define BLUE 0b001

bool red_knob_pressed(uint8_t *mem_base) 
{	
	uint32_t state = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
	bool r_knob_pressed = ((state >> 24) & RED); 
	return r_knob_pressed;
}

bool blue_knob_pressed(uint8_t *mem_base){
    uint32_t value = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    bool b_knob_pressed = ((value >> 24) & BLUE);
    return b_knob_pressed;
}

uint8_t red_knob(uint8_t *mem_base)
{
	int point = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);
	uint8_t r_knob = ((point >> 16) & 0xff);
	//printf("%" PRIu8 "\n", r_knob);
	return (uint8_t)(r_knob/4);
}

uint8_t blue_knob(uint8_t *mem_base)
{
	int point = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);
	uint8_t b_knob = ((point >> 0) & 0xff);
	// printf("%" PRIu8 "\n", g_knob);
	return (uint8_t)(b_knob/4);
}
