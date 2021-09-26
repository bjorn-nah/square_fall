#include <gb/gb.h>

#include "lib/utils.h"
#include "globals.h"

void run_gameover(void){
	uint8_t start;
	text_load_font();
	text_print_string_bkg(5, 7, "GAME  OVER");
	text_print_string_bkg(4, 9, "SCORE:");
	print_uint16_bkg(11, 9, score, 5);
	SHOW_BKG;
	DISPLAY_ON;
	start = 1;
	while(start){
		if(joypad() & J_START) {
			start = 2;
		}
		if(!joypad() && start==2) {
			start = 0;
		}
	}
	DISPLAY_OFF;
	HIDE_BKG;
	clear_bkg();
}