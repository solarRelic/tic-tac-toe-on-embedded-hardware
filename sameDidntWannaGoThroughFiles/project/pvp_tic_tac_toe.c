#include <stdbool.h>
#include <stdio.h>
#include "lcd_utils.h"
#include "input.h"
#include "drawing.h"
#include "mzapo_parlcd.h"
#include "pvp_tic_tac_toe.h"
#include "pvpc_tic_tac_toe.h"
#include "game_logic.h"
#include "struct.h"

const char PLAYER_1 = 'X';
const char PLAYER_2 = 'O';
const int ZERO_LIVES = 0x00000000;
bool PvP = true;

void vs_player(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *led_line, volatile uint32_t *rgb1, volatile uint32_t *rgb2)
{
    sleep(1);       // when entering tictactoePC, so that it doesn't press curr button automatically
    uint8_t option;

    bool quit = false;
    //init lives representation on led strip
    int a = 0xff000000;
    int b = 0x000000ff;

    while (!quit)
    {
		sleep(1/1000);
		printf("\nNew PvP game!\n");
        char play_again = ' ';

        int free_tiles = 9;
        int p1_move, p2_move;
        char winner = ' ';

        board_clear();
        draw_board(parlcd_mem_base, fb, fdes);
		board_printout_terminal();

        //turn on score board
        *led_line = a+b;

        while (winner == ' ' || free_tiles != 0)
        {
			draw_char(350, 65, PLAYER_2, 0x0000, fdes, 7, fb);
			draw_char(350, 65, PLAYER_1, 0xf000, fdes, 7, fb);
            p1_move = player_move(PLAYER_1, mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2, PvP);
            free_tiles--;
		    board_printout_terminal();
            update_board(p1_move, PLAYER_1, parlcd_mem_base, fdes, fb);
            winner = check_winner();
            if (winner != ' ' || free_tiles == 0)
            {
                break;
            }
			draw_char(350, 65, PLAYER_1, 0x0000, fdes, 7, fb);
			draw_char(350, 65, PLAYER_2, 0x000dff, fdes, 7, fb);
            p2_move = player_move(PLAYER_2, mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2, PvP);
            free_tiles--;
		    board_printout_terminal();
            update_board(p2_move, PLAYER_2, parlcd_mem_base, fdes, fb);
            winner = check_winner();
            if (winner != ' ' || free_tiles == 0)
            {
                break;
            }
        }
        
        if (winner == 'X') {
            a = a << 1;
        } else if (winner == 'O') {
            b = b >> 1;
        } 
        
        *led_line = a+b;
        if (a == ZERO_LIVES)
        {
            play_again = menu_game_over(PvP, winner, PLAYER_1, mem_base, parlcd_mem_base, fdes, fb, led_line, rgb1, rgb2);
        } else if (b == ZERO_LIVES) {
            play_again = menu_game_over(PvP, winner, PLAYER_1, mem_base, parlcd_mem_base, fdes, fb, led_line, rgb1, rgb2);
        } else {
            play_again = menu_replay(PvP, winner, PLAYER_1, mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2);
                
        }
        if (play_again != 'y')
            quit = true;
    }

    printf("Thanks for playing!\n");
}
