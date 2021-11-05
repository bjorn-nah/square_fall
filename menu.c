#include <gb/gb.h>

#include "lib/utils.h"
#include "globals.h"
#include "constants.h"

void run_menu(void){
	uint8_t start;
	clear_bkg();
	
	// sprite init
	if(game_mode == SCORE){
		move_sprite(0, 24, 24);
	}
	if(game_mode == PUZZLE){
		move_sprite(0, 24, 40);
	}
	SHOW_SPRITES;

	text_print_string_bkg(4, 1, "SCORE ATACK");
	text_print_string_bkg(4, 3, "PUZZLE");
	SHOW_BKG;
	DISPLAY_ON;
	fade_reset();
	start = 1;
	while(start){
		if(joypad() & J_UP) {
			game_mode = SCORE;
			move_sprite(0, 24, 24);
		}
		if(joypad() & J_DOWN) {
			game_mode = PUZZLE;
			move_sprite(0, 24, 40);
		}
		if(joypad() & J_START) {
			start = 0;
		}
	}
	fade_out(50);
	DISPLAY_OFF;
	HIDE_BKG;
	HIDE_SPRITES;
	clear_bkg();
}