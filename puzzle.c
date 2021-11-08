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
	uint8_t start, display_state;
	clear_bkg();

	//text_print_string_bkg(4, 3, "PUZZLE !");
	SHOW_BKG;
	DISPLAY_ON;
	fade_reset();
	
	display_state = DISPLAY;
	
	load_playground(playground_rle01);
	//init_playgrounds();
	draw_all();
	
	start = 1;
	while(start != 0){
		if(joypad() & J_START) {
			start = 0;
		}
	}
	
	fade_out(50);
	DISPLAY_OFF;
	HIDE_BKG;
	clear_bkg();
}