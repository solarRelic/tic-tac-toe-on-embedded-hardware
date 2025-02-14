#ifndef DRAWING_H
#define DRAWING_H

#include "font_types.h"

void draw_pixel(int x, int y, unsigned short color, unsigned short *fb);

void draw_pixel_big(int x, int y, unsigned short color, int scale, unsigned short *fb);

int char_width(int ch, font_descriptor_t *fdes);

void draw_char(int x, int y, char ch, unsigned short color, font_descriptor_t *fdes, int scale, unsigned short *fb);

void draw_string(int x, int y, int more, char *text, unsigned short color, font_descriptor_t *fdes, int scale, unsigned short *fb);

void draw_board(unsigned char *parlcd_mem_base, unsigned short *fb, font_descriptor_t *fdes);

void draw_square(int x, int y, unsigned short color, unsigned short *fb);

void draw_num_1(font_descriptor_t *fdes, unsigned short *fb);
void draw_num_2(font_descriptor_t *fdes, unsigned short *fb);
void draw_num_3(font_descriptor_t *fdes, unsigned short *fb);
void draw_num_4(font_descriptor_t *fdes, unsigned short *fb);
void draw_num_5(font_descriptor_t *fdes, unsigned short *fb);
void draw_num_6(font_descriptor_t *fdes, unsigned short *fb);
void draw_num_7(font_descriptor_t *fdes, unsigned short *fb);
void draw_num_8(font_descriptor_t *fdes, unsigned short *fb);
void draw_num_9(font_descriptor_t *fdes, unsigned short *fb);


#endif
