#ifndef MENU_H
#define MENU_H

#include "font_types.h"

void menu_default(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *led_line);
void selection_arrow_main(uint8_t option, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2);
void selection_arrow_mode(uint8_t option, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2);
void menu_mode(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2, volatile uint32_t *led_line);
void selection_arrow_choose_side(uint8_t option, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2);
int menu_choose_side(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2);
void selection_arrow_replay(uint8_t option, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb);
char menu_replay(bool is_pvp, const char winner, const char player, uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2);
void menu_help(uint8_t *mem_base, unsigned char *lcd_mem_base, font_descriptor_t *fdes, unsigned short *fb);
char menu_game_over(bool is_pvp, const char winner, const char player, uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *led_line, volatile uint32_t *rgb1, volatile uint32_t *rgb2);
void menu_goodbye(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2, volatile uint32_t *led_line);

#endif