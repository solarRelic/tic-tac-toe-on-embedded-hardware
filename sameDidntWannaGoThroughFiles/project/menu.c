#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#include "menu.h"
#include "input.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "pvpc_tic_tac_toe.h"
#include "pvp_tic_tac_toe.h"
#include "struct.h"



void menu_default(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *led_line)
{
    *led_line = 0xffffffff;
    display_black(parlcd_mem_base, fb);

    int title_font = 4;
	draw_string(80, 20, 4, "Tic-Tac-Toe", 0xffff, fdes, title_font, fb);

    int medium_font = 3;
	draw_string(150, 105, 3, "Play", 0xffffff, fdes, medium_font, fb); 
	draw_string(150, 155, 3, "Help", 0xffffff, fdes, medium_font, fb);
    draw_string(150, 205, 3, "Quit", 0xffffff, fdes, medium_font, fb); 

    int little_font = 1;
	draw_string(80, 285, 1, "game implemenation by: Nguyen, Batuev", 0xffff, fdes, little_font, fb);

	display_reveal(parlcd_mem_base, fb); 
}

void selection_arrow_main(uint8_t option, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2)
{
    int medium_font = 3;
    

    draw_string(270, 105, 3, "<--", 0x0000, fdes, medium_font, fb);
    draw_string(270, 155, 3, "<--", 0x0000, fdes, medium_font, fb);
    draw_string(270, 205, 3, "<--", 0x0000, fdes, medium_font, fb);
    //lights up rgb
    switch(option){
        case 0:
	        *rgb1 = ((union led){.r = 0xfc, .g = 0x00, .b = 0x00}).data;
	        *rgb2 = ((union led){.r = 0xfc, .g = 0x00, .b = 0x00}).data;
            draw_string(270, 105 + 50 * option, 3, "<--", 0x000dff, fdes, medium_font, fb);

            break;
        case 1:
	        *rgb1 = ((union led){.r = 0x00, .g = 0xaf, .b = 0x00}).data;
	        *rgb2 = ((union led){.r = 0x00, .g = 0xaf, .b = 0x00}).data;
            draw_string(270, 105 + 50 * option, 3, "<--", 0x0f00, fdes, medium_font, fb);

            break;
        case 2:
        	*rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0xfc}).data;
	        *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0xfc}).data;
            draw_string(270, 105 + 50 * option, 3, "<--", 0xf000, fdes, medium_font, fb);

            break;

    }
    display_reveal(parlcd_mem_base, fb);
}

void selection_arrow_mode(uint8_t option, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2)
{
    int medium_font = 3;
    draw_string(330, 115, 3, "<--", 0x0000, fdes, medium_font, fb);
    draw_string(330, 165, 3, "<--", 0x0000, fdes, medium_font, fb);
    draw_string(330, 215, 3, "<--", 0x0000, fdes, medium_font, fb);
    switch(option){
        case 0:
	        *rgb1 = ((union led){.r = 0xfc, .g = 0x00, .b = 0x00}).data; //fc
	        *rgb2 = ((union led){.r = 0xfc, .g = 0x00, .b = 0x00}).data;
            draw_string(330, 115 + 50 * option, 3, "<--", 0x000dff, fdes, medium_font, fb);

            break;
        case 1:
	        *rgb1 = ((union led){.r = 0x00, .g = 0xaf, .b = 0x00}).data; //af
	        *rgb2 = ((union led){.r = 0x00, .g = 0xaf, .b = 0x00}).data;
            draw_string(330, 115 + 50 * option, 3, "<--", 0x0f00, fdes, medium_font, fb);

            break;
        case 2:
        	*rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0xfc}).data; //fc
	        *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0xfc}).data;
            draw_string(330, 115 + 50 * option, 3, "<--", 0xf000, fdes, medium_font, fb);

            break;

    }
    display_reveal(parlcd_mem_base, fb);
}
void menu_mode(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2, volatile uint32_t *led_line)
{
    sleep(1);       //when entering mode, so that it doesn't press curr button automatically
    printf("\nIn the game mode menu.\n");
    display_black(parlcd_mem_base, fb);

    int title_font = 4;
	draw_string(80, 40, 4, "Game mode:", 0xffff, fdes, title_font, fb);

    int normal_font = 2;
	draw_string(80, 125, 2, "versus PC", 0xffff, fdes, normal_font, fb);
	draw_string(80, 175, 2, "versus Player", 0xffff, fdes, normal_font, fb);
	draw_string(80, 225, 2, "Back", 0xffff, fdes, normal_font, fb);

    display_reveal(parlcd_mem_base, fb);

    bool quit = false;
	uint8_t option;
    while (!quit)
    {
    	option = red_knob(mem_base) % 3;
        selection_arrow_mode(option, parlcd_mem_base, fdes, fb, rgb1, rgb2);
		if (red_knob_pressed(mem_base))
		{
			switch(option) 
			{
			case 0:
                vs_pc(mem_base, parlcd_mem_base, fdes, fb, rgb1, rgb2);
                quit = true;
				break;
			case 1:
                vs_player(mem_base, parlcd_mem_base, fdes, fb, led_line, rgb1, rgb2);
                quit = true;
				break;
			case 2:
                quit = true;
				break;
			default:
                quit = true;
				break;
			}
		}
    }
}

void selection_arrow_choose_side(uint8_t option, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2)
{
    int medium_font = 3;
    draw_string(250, 135, 3, "<--", 0x0000, fdes, medium_font, fb);
    draw_string(250, 215, 3, "<--", 0x0000, fdes, medium_font, fb);
    switch(option){
        case 0:
            draw_string(250, 135, 3, "<--", 0x000dff, fdes, medium_font, fb);
            *rgb1 = ((union led){.r = 0xfc, .g = 0x00, .b = 0x00}).data; //fc
	        *rgb2 = ((union led){.r = 0xfc, .g = 0x00, .b = 0x00}).data;
            break;
        case 1:
            draw_string(250, 215, 3, "<--", 0x0f00, fdes, medium_font, fb);
            *rgb1 = ((union led){.r = 0x00, .g = 0xaf, .b = 0x00}).data; //af
	        *rgb2 = ((union led){.r = 0x00, .g = 0xaf, .b = 0x00}).data;
            break;
    }
    display_reveal(parlcd_mem_base, fb);
}
int menu_choose_side(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2)
{
    sleep(1);
    display_black(parlcd_mem_base, fb);

    int semi_title = 3;
    draw_string(50, 40, 3, "Choose your side:", 0xffff, fdes, semi_title, fb);

    draw_char(170, 115, 'X', 0xffff, fdes, 6, fb);
    draw_char(170, 200, 'O', 0xffff, fdes, 6, fb);

    display_reveal(parlcd_mem_base, fb);

    int side;

    bool quit = false;
	uint8_t option;
    while (!quit) 
    {
    	option = red_knob(mem_base) % 2;
        selection_arrow_choose_side(option, parlcd_mem_base, fdes, fb, rgb1, rgb2);
        if (red_knob_pressed(mem_base))
        {
            switch (option)
            {
            case 0:
                side = 1;
                quit = true;
                break;
            case 1:
                side = 2;
                quit = true;
                break;
            default:
                quit = true;
                break;
            }
            }
    }
    return side;
}

void selection_arrow_replay(uint8_t option, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb)
{
    int medium_font = 3;
    draw_string(280, 135, 3, "<--", 0x0000, fdes, medium_font, fb);
    draw_string(280, 185, 3, "<--", 0x0000, fdes, medium_font, fb);
    draw_string(280, 135 + 50 * option, 3, "<--", 0xffff, fdes, medium_font, fb);
    display_reveal(parlcd_mem_base, fb);
}
char menu_replay(bool is_pvp, const char winner, const char player, uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2)
{
    sleep(1);
    display_black(parlcd_mem_base, fb);

    const char computer = (player == 'X') ? 'O' : 'X';

    int title_font = 4;
    if (is_pvp) 
    {
        int semi_title = 3;
        if (winner == 'X')
        {
            draw_string(70, 30, 3, "Player 1 has won!", 0xffff, fdes, semi_title, fb);
        }
        else if (winner == 'O')
        {
            draw_string(70, 30, 3, "Player 2 has won!", 0xffff, fdes, semi_title, fb);
        }
        else
        {
            draw_string(100, 20, 4, "It's a tie!", 0xffff, fdes, title_font, fb);
            for(int i = 0; i < 5; i++){
                *rgb1 = ((union led){.r = 0xff, .g = 0xff, .b = 0xff}).data;
                *rgb2 = ((union led){.r = 0xff, .g = 0xff, .b = 0xff}).data;
                usleep(100000);
                *rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                usleep(100000);
            }  
        }
    }
    else
    {
        if (winner == player)
        {
            draw_string(80, 20, 4, "You've won!", 0xffff, fdes, title_font, fb);
                for(int i = 0; i < 5; i++){
                    *rgb1 = ((union led){.r = 0x00, .g = 0xff, .b = 0x00}).data;
                    *rgb2 = ((union led){.r = 0x00, .g = 0xff, .b = 0x00}).data;

                    usleep(100000);
                    *rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                    *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;

                    usleep(100000);
        
                }   
            }
        else if (winner == computer)
        {
            draw_string(80, 20, 4, "You've lost!", 0xffff, fdes, title_font, fb);
            for(int i = 0; i < 5; i++){
                *rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0xff}).data;
                *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0xff}).data;
                usleep(100000);
                *rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                usleep(100000);
            }  
        }
        else
        {
            draw_string(100, 20, 4, "It's a tie!", 0xffff, fdes, title_font, fb);
            for(int i = 0; i < 5; i++){
                *rgb1 = ((union led){.r = 0xff, .g = 0xff, .b = 0xff}).data;
                *rgb2 = ((union led){.r = 0xff, .g = 0xff, .b = 0xff}).data;
                usleep(100000);
                *rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                usleep(100000);
            }  
        }
    }

    char response = ' ';
    int normal_font = 2;
    draw_string(30, 145, 2, "Play again", 0xffff, fdes, normal_font, fb);
    draw_string(30, 195, 2, "Back to menu", 0xffff, fdes, normal_font, fb);

    display_reveal(parlcd_mem_base, fb);

    bool quit = false;
	uint8_t option;
    while (!quit) 
    {
    	option = red_knob(mem_base) % 2;
        selection_arrow_replay(option, parlcd_mem_base, fdes, fb);
        if (red_knob_pressed(mem_base))
        {
            switch (option)
            {
            case 0:
                response = 'y';
                quit = true;
                break;
            case 1:
                response = 'n';
                quit = true;
                break;
            default:
                quit = true;
                break;
            }
            }
    }
    return response;
}

void menu_help(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb)
{
    sleep(1);       //when entering help, so that it doesn't press curr button automatically 
    display_black(parlcd_mem_base, fb);

    bool quit = false;
    while (!quit) 
    {
        int title_font = 4;
        draw_string(45, 20, 4, "HOW TO PLAY", 0xffff, fdes, title_font, fb);

        int little_font = 1;
        draw_string(25, 105, 1, "Red knob:", 0xf000, fdes, little_font, fb);
        draw_string(125, 105, 1, "Moving up, down and confirms the choice", 0xffff, fdes, little_font, fb);
        draw_string(125, 125, 1, "by pressing in menu.", 0xffff, fdes, little_font, fb);
        draw_string(125, 155, 1, "Controls Player1 in PvP and PvPC.", 0xffff, fdes, little_font, fb);

        draw_string(25, 215, 1, "Blue knob:", 0x000dff, fdes, little_font, fb);
        draw_string(125, 215, 1, "Controls Player2 in PvP.", 0xffff, fdes, little_font, fb);
    
        int medium_font = 3;
        draw_string(310, 255, 4, "BACK", 0xf000, fdes, medium_font, fb);

        display_reveal(parlcd_mem_base, fb); 

        if (red_knob_pressed(mem_base)) {
            quit = true;
        }
    }
}

char menu_game_over(bool is_pvp, const char winner, const char player, uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *led_line, volatile uint32_t *rgb1, volatile uint32_t *rgb2){
    sleep(1);
    display_black(parlcd_mem_base, fb);

    const char computer = (player == 'X') ? 'O' : 'X';

    int title_font = 4;
    if (is_pvp) 
    {
        int semi_title = 1;
        if (winner == 'X')
        {
            draw_string(70, 30, title_font, "Player 1 won", 0xf000, fdes, title_font, fb);
            draw_string(150, 110, semi_title, "(Player 2 lost all his lives)", 0xffff, fdes, semi_title, fb);
            for(int i = 0; i < 5; i++){
                *rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0xff}).data;
                *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0xff}).data;
                usleep(100000);
                *rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                usleep(100000);
            }  
        }
        else if (winner == 'O')
        { 
            draw_string(70, 30, title_font, "Player 2 won", 0x000dff, fdes, title_font, fb);
            draw_string(150, 110, semi_title, "(Player 1 lost all his lives)", 0xffff, fdes, semi_title, fb);
            for(int i = 0; i < 5; i++){
                *rgb1 = ((union led){.r = 0xff, .g = 0x00, .b = 0x00}).data;
                *rgb2 = ((union led){.r = 0xff, .g = 0x00, .b = 0x00}).data;
                usleep(100000);
                *rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                *rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                usleep(100000);
            }  
        }
    }
    int normal_font = 2;
    draw_string(150, 210, normal_font, "Back to menu", 0xf000, fdes, normal_font, fb);

    display_reveal(parlcd_mem_base, fb);
    char response = ' ';
    bool quit = false;
    while (!quit){
        *led_line = 0xaaaaaaaa;
        *rgb1 = ((union led){.r = 0x25, .g = 0x79, .b = 0xf1}).data;
		*rgb2 = ((union led){.r = 0x25, .g = 0x79, .b = 0xf1}).data;
        usleep(100000); //5500
        *led_line = 0xaaaaaaaa ^ 0xffffffff;
		*rgb1 = ((union led){.r = 0x7b, .g = 0x00, .b = 0x6b}).data;
		*rgb2 = ((union led){.r = 0x7b, .g = 0x00, .b = 0x6b}).data;
		usleep(100000);
        if(red_knob_pressed(mem_base)){
            response = 'n';
            quit = true;
        }
    }
    return response;
}

void menu_goodbye(uint8_t *mem_base, unsigned char *parlcd_mem_base, font_descriptor_t *fdes, unsigned short *fb, volatile uint32_t *rgb1, volatile uint32_t *rgb2, volatile uint32_t *led_line)
{
    display_black(parlcd_mem_base, fb);

				draw_string(75, 105, 5, "Goodbye!", 0xffff, fdes, 5, fb);
				display_reveal(parlcd_mem_base, fb);

				for(int i = 0; i < 10; i++){
					*led_line = 0xffffffff;
					*rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0xff}).data;
					*rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0xff}).data;
                    usleep(70000);
        			*led_line = 0x00000000;
					*rgb1 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
					*rgb2 = ((union led){.r = 0x00, .g = 0x00, .b = 0x00}).data;
                    usleep(70000);
				}  
}