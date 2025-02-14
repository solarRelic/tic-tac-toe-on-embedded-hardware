#include <stdlib.h>
#include <string.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "drawing.h"

void draw_pixel(int x, int y, unsigned short color, unsigned short *fb)
{
    if (x >= 0 && x < 480 && y >= 0 && y < 320)
    {
        fb[x + 480 * y] = color;
    }
}

void draw_pixel_big(int x, int y, unsigned short color, int scale, unsigned short *fb)
{
    int i, j;
    for (i = 0; i < scale; i++)
    {
        for (j = 0; j < scale; j++)
        {
            draw_pixel(x + i, y + j, color, fb);
        }
    }
}

int char_width(int ch, font_descriptor_t *fdes)
{
    int width;
    if (!fdes->width)
    {
        width = fdes->maxwidth;
    }
    else
    {
        width = fdes->width[ch - fdes->firstchar];
    }
    return width;
}

void draw_char(int x, int y, char ch, unsigned short color, font_descriptor_t *fdes, int scale, unsigned short *fb)
{
    int w = char_width(ch, fdes);
    const font_bits_t *ptr;
    if ((ch >= fdes->firstchar) && (ch - fdes->firstchar < fdes->size))
    {
        if (fdes->offset)
        {
            ptr = &fdes->bits[fdes->offset[ch - fdes->firstchar]];
        }
        else
        {
            int bw = (fdes->maxwidth + 15) / 16;
            ptr = &fdes->bits[(ch - fdes->firstchar) * bw * fdes->height];
        }
        int i, j;
        for (i = 0; i < fdes->height; i++)
        {
            font_bits_t val = *ptr;
            for (j = 0; j < w; j++)
            {
                if ((val & 0x8000) != 0)
                {
                    draw_pixel_big(x + scale * j, y + scale * i, color, scale, fb);
                }
                val <<= 1;
            }
            ptr++;
        }
    }
}

void draw_string(int x, int y, int more, char *text, unsigned short color, font_descriptor_t *fdes, int scale, unsigned short *fb)
{
    for (int i = 0; i < strlen(text); i++)
    {
        draw_char(x, y, text[i], color, fdes, scale, fb);
        x += more * char_width(text[i], fdes) + 1;
    }
}

void draw_board(unsigned char *parlcd_mem_base, unsigned short *fb, font_descriptor_t *fdes)
{

    display_black(parlcd_mem_base, fb);

    for (int i = 15; i <= 195; i += 90) {
        for (int j = 30; j <= 210; j += 90) {
            draw_square(i, j, 0xFFFF, fb);
        }
    }

    char t = 49;
    for(int i = 62; i <= 242; i+=90){
        for(int j = 52; j <= 232; j+=90){
            draw_char(j, i, t, 0xffff, fdes, 2, fb);
            t++;
        }
    }
    draw_string(300, 25, 2, "move:", 0xffff, fdes, 2, fb);

    draw_string(300, 180, 2, "place on tile:", 0xffff, fdes, 2, fb);

    display_reveal(parlcd_mem_base, fb);

}

void draw_square(int x, int y, unsigned short color, unsigned short *fb)
{
    for (int i = 0; i < 90; ++i) {
        for (int j = 0; j < 90; ++j) {
            int posx = i + x;
            int posy = j + y;
            if (posx <= x + 2 && posx >= x || posy <= y + 2 && posy >= y
                || posx >= x + 90 - 3 && posx <= x + 90 - 1 ||
                posy >= y + 90 - 3 && posy <= y + 90 - 1) {
                draw_pixel(posx, posy, color, fb);
            }
        }
    }
}

void draw_num_1(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '2', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '1', 0xffff, fdes, 3, fb);
}

void draw_num_2(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '1', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '2', 0xffff, fdes, 3, fb);
}

void draw_num_3(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '1', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '2', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0xffff, fdes, 3, fb);
}

void draw_num_4(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '1', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '2', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0xffff, fdes, 3, fb);
}

void draw_num_5(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '1', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '2', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0xffff, fdes, 3, fb);
}

void draw_num_6(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '1', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '2', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0xffff, fdes, 3, fb);
}

void draw_num_7(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '1', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '2', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0xffff, fdes, 3, fb);
}

void draw_num_8(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '1', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '2', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0xffff, fdes, 3, fb);
}

void draw_num_9(font_descriptor_t *fdes, unsigned short *fb)
{
    draw_char(375, 220, '1', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '2', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '3', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '4', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '5', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '6', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '7', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '8', 0x0000, fdes, 3, fb);
    draw_char(375, 220, '9', 0xffff, fdes, 3, fb);
}

