#include <gb/gb.h>

#include "lib/utils.h"
#include "lib/game_commons.h"
#include "constants.h"
#include "lib/game_vars.h"

UBYTE playground_rle01[] = {
	2, 1, 4, 2 , 4, 1,
	6, 2, 2, 1,
	8, 2, 1, 1,
	9, 2,
	9, 2,
	9, 1,
	9, 2,
	9, 2,
	9, 1
	/*
	1,  1,  2,  2,  2,  2,  1,  1, 3,
	1,  2,  2,  2,  2,  2,  2,  1, 3,
	2,  2,  2,  2,  2,  2,  2,  2, 3,
	2,  2,  1,  2,  1,  2,  2,  2, 3,
	2,  2,  1,  2,  1,  2,  2,  2, 3,
	2,  2,  2,  1,  2,  2,  2,  1, 3,
	1,  2,  2,  2,  2,  2,  1,  1, 3,
	1,  2,  2,  2,  2,  2,  1,  1, 3,
	1,  2,  1,  2,  1,  2,  1,  1, 3
	*/
};



void run_puzzle(void){
	//uint8_t start, display_state;
	//uint8_t cursor_x, cursor_y, cursor_state, action_state, display_state;
	uint8_t  start;
	
	cursor_x = 4;
	cursor_y = 4;
	cursor_state = WAIT;
	action_state = WAIT;
	display_state = DISPLAY;
	bomb = 10;
	
	clear_bkg();

	//text_print_string_bkg(4, 3, "PUZZLE !");
	SHOW_BKG;
	DISPLAY_ON;
	fade_reset();
	
	display_state = DISPLAY;
	
	load_playground(playground_rle01);
	//init_playgrounds();
	draw_all();
	
	// sprite init
	place_cursor(cursor_x, cursor_y);
	SHOW_SPRITES;
	
	start = 1;
	while(start){
		
		// if display_state == WAIT
		if(!display_state){
			
			physics_puzzle();
			
			if(cursor_state == WAIT){
				if(joypad() & J_UP) {
					cursor_state = UP;
				}
				if(joypad() & J_DOWN) {
					cursor_state = DOWN;
				}
				if(joypad() & J_RIGHT) {
					cursor_state = RIGHT;
				}
				if(joypad() & J_LEFT) {
					cursor_state = LEFT;
				}
				move_cursor(cursor_x, cursor_y, cursor_state);
			}
			place_cursor(cursor_x, cursor_y);
			
			if(action_state == WAIT) {
				if(joypad() & J_A) {
					action_state = ACTION_A;
				}
			}
					
			// if no directions are pressed, resert cursor_state
			if(!(joypad() & 0x0FU) && action_state == WAIT){
				cursor_state = WAIT;
			}
				


			if(joypad() & J_START) {
				start = 0;
			}
		}
		else{	// if display_state != WAIT
			draw_all();
		}
	}
	
	fade_out(50);
	DISPLAY_OFF;
	HIDE_SPRITES;
	HIDE_BKG;
	clear_bkg();
}