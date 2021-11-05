#include <gb/gb.h>

#include "lib/utils.h"

void run_puzzle(void){
	uint8_t start;
	clear_bkg();

	text_print_string_bkg(4, 3, "PUZZLE !");
	SHOW_BKG;
	DISPLAY_ON;
	fade_reset();
	start = 1;
	while(start){
		if(joypad() & J_START) {
				start = 0;
			}
	}
	fade_out(50);
	DISPLAY_OFF;
	HIDE_BKG;
	clear_bkg();
}