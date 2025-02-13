#include "mzapo_regs.h"

#include "lcd_utils.h"

void display_black_2(unsigned char *parlcd_mem_base, unsigned short *fb)
{
	for (int ptr = 0; ptr < 320 * 480 ; ptr++) {
		fb[ptr] = 0;
	}
}

void display_reveal(unsigned char *parlcd_mem_base, unsigned short *fb)
{
	parlcd_write_cmd(parlcd_mem_base, 0x2c);
	for (int ptr = 0; ptr < 320 * 480 ; ptr++) {
		parlcd_write_data(parlcd_mem_base, fb[ptr]);
	}
}

void display_black(unsigned char *parlcd_mem_base, unsigned short *fb)
{
	parlcd_write_cmd(parlcd_mem_base, 0x2c);
	for (int ptr = 0; ptr < 320 * 480 ; ptr++) {
		fb[ptr] = 0;
		parlcd_write_data(parlcd_mem_base, fb[ptr]);
	}
	/* the same
	parlcd_write_cmd(parlcd_mem_base, 0x2c);
	int ptr = 0;
	for (int i = 0; i < 320; i++)
	{
		for (int j = 0; j < 480; j++)
		{
			fb[ptr] = 0;
			parlcd_write_data(parlcd_mem_base, fb[ptr++]);
		}
	}
	*/
}
