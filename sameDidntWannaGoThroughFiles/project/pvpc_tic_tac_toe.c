
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include "pvpc_tic_tac_toe.h"
#include "font_types.h"
#include "mzapo_parlcd.h"
#include "lcd_utils.h"
#include "drawing.h"
#include "game_logic.h"

char PLAYER;
char COMPUTER;

bool pvp = false;

void vs_pc(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2)
{
	bool quit = false;
	while (!quit)
	{
		sleep(1);
		int chosen_side = menu_choose_side(mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2);
		if (chosen_side == 1)
		{
			PLAYER = 'X';
			COMPUTER = 'O';
		}
		else
		{
			PLAYER = 'O';
			COMPUTER = 'X';
		}
		sleep(1);

		printf("\nNew game!\n");
		char play_again = ' ';

		int free_tiles = 9;
		int p_move, pc_move;
		char winner = ' ';

		board_clear();
		draw_board(parlcd_mem_base, fb, fdes);
		board_printout_terminal();

		while (winner == ' ' || free_tiles != 0)
		{	
			if (chosen_side == 1)
			{
				p_move = player_move(PLAYER, mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2, pvp);
				free_tiles--;
				board_printout_terminal();
				update_board(p_move, PLAYER, parlcd_mem_base, fdes, fb);

				draw_char(350, 65, PLAYER, 0x0000, fdes, 7, fb);
				draw_char(350, 65, COMPUTER, 0xffff, fdes, 7, fb);
				display_reveal(parlcd_mem_base, fb);

				winner = check_winner();
				if (winner != ' ' || free_tiles == 0)
				{
					break;
				}
				chosen_side = 2;
			}

			if (chosen_side = 2)
			{
				pc_move = computer_move(COMPUTER, PLAYER);
				free_tiles--;
				board_printout_terminal();
				update_board(pc_move, COMPUTER, parlcd_mem_base, fdes, fb);

				draw_char(350, 65, COMPUTER, 0x0000, fdes, 7, fb);
				draw_char(350, 65, PLAYER, 0xffff, fdes, 7, fb);
				display_reveal(parlcd_mem_base, fb);

				winner = check_winner();
				if (winner != ' ' || free_tiles == 0)
				{
					break;
				}
				chosen_side = 1;
			}
		}

		play_again = menu_replay(pvp, winner, PLAYER, mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2);
		if (play_again != 'y')
			quit = true;
	}

	printf("\nThanks for playing!\n");
}
