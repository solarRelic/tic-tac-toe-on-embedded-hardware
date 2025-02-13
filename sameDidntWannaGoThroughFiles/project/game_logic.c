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
#include "struct.h"

int board[3][3];

int player_move(char side, uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2, bool pvp)
{
	bool player1 = true;
	if(pvp){
    	player1 = (side == 'X') ? true : false;
	}
	
	uint8_t option;
	int move = 0;
	while (true)
	{
		int normal_font = 2;
		draw_string(295, 270, 2, "invalid move", 0x0000, fdes, normal_font, fb);
		while ((!red_knob_pressed(mem_base) && player1) || (!blue_knob_pressed(mem_base) && !player1))
		{
            if(player1)
            {
                option = red_knob(mem_base) % 9;
            } 
            else 
            {
                option = blue_knob(mem_base) % 9;
			} 
            
			switch (option)
			{
				case 0:
					draw_num_1(fdes, fb);
					move = 1;
					break;
				case 1:
					draw_num_2(fdes, fb);
					move = 2;
					break;
				case 2:
					draw_num_3(fdes, fb);
					move = 3;
					break;
				case 3:
					draw_num_4(fdes, fb);
					move = 4;
					break;
				case 4:
					draw_num_5(fdes, fb);
					move = 5;
					break;
				case 5:
					draw_num_6(fdes, fb);
					move = 6;
					break;
				case 6:
					draw_num_7(	fdes, fb);
					move = 7;
					break;
				case 7:
					draw_num_8(fdes, fb);
					move = 8;
					break;
				case 8:
					draw_num_9(fdes, fb);
					move = 9;
					break;
				default:
					break;
			}
			display_reveal(parlcd_mem_base, fb);
		}

		int row = (move - 1) / 3;
		int col = (move - 1) - row * 3;
		if (board[row][col] == ' ')
		{
			board[row][col] = side;
			printf("\nmove is made on %d x %d\n", row, col);
			break;
		}
		else
		{
			draw_string(295, 270, 2, "invalid move", 0xffff, fdes, normal_font, fb);
			display_reveal(parlcd_mem_base, fb);
			printf("invalid move\n");
		}

		for(int i = 0; i < 150;i++)
		{
			*rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0xff}).data;
			*rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0xff}).data;

			usleep(1500);
			*rgb1 = ((union led){.r = 0xff, .g = 0x00, .b = 0x00}).data;
			*rgb2 = ((union led){.r = 0xff, .g = 0x00, .b = 0x00}).data;

			usleep(1500);
		}
		*rgb1 = ((union led){.r = 0x00, .g = 0xaf, .b = 0x00}).data;
		*rgb2 = ((union led){.r = 0x00, .g = 0xaf, .b = 0x00}).data;
	}
	return move;

}
void update_board(int move, char player, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb)
{
	switch(move)
	{
		case 1:
			draw_char(52, 62, '1', 0x0000, fdes, 2, fb);
			draw_char(37, 37, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
		case 2:
			draw_char(142, 62, '2', 0x0000, fdes, 2, fb);
			draw_char(127, 37, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
		case 3:
			draw_char(232, 62, '3', 0x0000, fdes, 2, fb);
			draw_char(217, 37, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
		case 4:
			draw_char(52, 152, '4', 0x0000, fdes, 2, fb);
			draw_char(37, 127, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
		case 5:
			draw_char(142, 152, '5', 0x0000, fdes, 2, fb);
			draw_char(127, 127, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
		case 6:
			draw_char(232, 152, '6', 0x0000, fdes, 2, fb);
			draw_char(217, 127, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
		case 7:
			draw_char(52, 242, '7', 0x0000, fdes, 2, fb);
			draw_char(37, 217, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
		case 8:
			draw_char(142, 242, '8', 0x0000, fdes, 2, fb);
			draw_char(127, 217, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
		case 9:
			draw_char(232, 242, '9', 0x0000, fdes, 2, fb);
			draw_char(217, 217, player, 0xffff, fdes, 5, fb);
			display_reveal(parlcd_mem_base, fb);
			break;
	}
}

void board_clear()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void board_printout_terminal()
{

	// terminal----------------------------------------------------
	printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
	printf("\n");
}

char check_winner()
{	
	// check rows
	for (int i = 0; i < 3; i++)
	{
		if ((board[i][0] == board[i][1] && board[i][0] == board[i][2]) && board[i][0] != ' ')
		{
			return board[i][0];
		}
	}

	// check columns
	for (int i = 0; i < 3; i++)
	{
		if ((board[0][i] == board[1][i] && board[0][i] == board[2][i]) && board[0][i] != ' ')
		{
			return board[0][i];
		}
	}

	// check diagonals
	if ((board[0][0] == board[1][1] && board[0][0] == board[2][2]) && board[0][0] != ' ')
	{
		return board[0][0];
	}
	if ((board[0][2] == board[1][1] && board[0][2] == board[2][0]) && board[0][2] != ' ')
	{
		return board[0][2];
	}

	return ' ';
}
int computer_move(char COMPUTER, char player)
{
	sleep(1);
	srand(time(0));
	//value of board
	int docasny[3][3] = {
		{9,7,9},
		{7,8,7},
		{9,7,9},
	};
	int pc_move;
	int row;
	int col;
	int move = 0;
	//if win
	for(int i =0;i<3;i++){
		for(int j =0;j<3;j++){
			move++;
			if (board[i][j] == ' '){
				board[i][j] = COMPUTER;
				char win = check_winner();
				if (win != ' '){
					printf("\npc move at %d x %d\n", i, j);
					return move;
				}
				board[i][j] = ' ';
			}
		}
	}
	move = 0;
	//block win
	for(int i =0;i<3;i++){
		for(int j =0;j<3;j++){
			move++;
			if (board[i][j] == ' '){
				board[i][j] = player;
				char win = check_winner();
				if (win != ' '){
					board[i][j] = COMPUTER;
					printf("\npc move at %d x %d\n", i, j);
					return move;
				}
				board[i][j] = ' ';
			}
		}
	}
	//make his move based on value of board
	int best = 0;
	move = 0;
	int max = 0;
	for(int i = 0; i<3; i++){
		for(int j = 0; j<3; j++){
			move++;
			if(max < docasny[i][j] && board[i][j] == ' '){
				best = move;
				max = docasny[i][j];
				row = i;
				col = j;
			}
		}
	}
	board[row][col] = COMPUTER;
	printf("\npc move at %d x %d\n", row, col);
	return best;
}
