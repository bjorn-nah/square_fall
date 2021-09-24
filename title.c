#include <gb/gb.h>

#include "lib/utils.h"

void run_title(void){
	uint8_t start;
	text_load_font();
	text_print_string_bkg(1, 1, "SQUARE FALL");
	text_print_string_bkg(1, 3, "PRESS START");
	SHOW_BKG;
	DISPLAY_ON;
	start = 1;
	while(start){
		if(joypad() & J_START) {
				start = 0;
			}
	}
	DISPLAY_OFF;
	HIDE_BKG;
	clear_bkg();
}