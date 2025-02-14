#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "font_types.h"

void update_board(int move, const char side, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb);

void update(int tile, const char side, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb);

int player_move(char side, uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2, bool pvp);

void board_clear();

void board_printout();

int free_tiles_left();

int computer_move();

char check_winner();

#endif