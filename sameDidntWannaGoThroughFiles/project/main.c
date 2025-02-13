/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON
 
  include your name there and license for distribution.
 
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "drawing.h"
#include "menu.h"
#include "lcd_utils.h"
#include "input.h"
#include "pvpc_tic_tac_toe.h"
#include "pvp_tic_tac_toe.h"
#include "struct.h"

int main(int argc, char *argv[])
{	
	//init rgb and led strip
	volatile void *spiled_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  	assert(spiled_base != NULL);
	volatile uint32_t *rgb1 = (spiled_base + SPILED_REG_LED_RGB1_o);
	volatile uint32_t *rgb2 = (spiled_base + SPILED_REG_LED_RGB2_o);
	volatile uint32_t *led_line = (spiled_base + SPILED_REG_LED_LINE_o);
	font_descriptor_t *fdes = &font_winFreeSystem14x16;
	//init lcd
	unsigned short fb[320 * 480 * 2];
	unsigned char *parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
	if (parlcd_mem_base == NULL)
		exit(1);
	parlcd_hx8357_init(parlcd_mem_base);
	parlcd_write_cmd(parlcd_mem_base, 0x2c);
	//init knob
	uint8_t *mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
	
	menu_default(parlcd_mem_base, mem_base, fdes, fb, led_line);

    bool quit = false;
	uint8_t option;
	while (!quit) 
	{
			
    	option = red_knob(mem_base) % 3;
		selection_arrow_main(option, parlcd_mem_base, fdes, fb, rgb1, rgb2);
		if (red_knob_pressed(mem_base))
		{
			switch(option) 	
			{
			case 0:
				printf("\nchanging to mode menu, option: %d\n", option);
				menu_mode(mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2, led_line);
				printf("\nreturned to main menu from mode\n");
				usleep(250000);		// when returning from menu, so that it doesn't press curr button automatically
				menu_default(parlcd_mem_base, mem_base, fdes, fb, led_line);
				break;
			case 1:
				printf("\nchanging to help menu, option: %d\n", option);
				menu_help(mem_base, parlcd_mem_base, fdes, fb);
				printf("\nreturned to main menu from help\n");
				usleep(250000);		// when returning from help, so that it doesn't press curr button automatically
				menu_default(mem_base, parlcd_mem_base, fdes, fb, led_line);
				break;
			case 2:
				menu_goodbye(mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2, led_line);
                quit = true;
				break;
			default:
                quit = true;
				break;
			}
		}
	}

	*led_line = 0x00000000;
	display_black(parlcd_mem_base, fb);
	printf("turning off the screen (blacking)\n");
	return 0;
}
