#include <gb/gb.h>

#include "title_art.c"

#include "lib/utils.h"
#include "globals.h"

void run_title(void){
	uint8_t start;
	clear_bkg();
	switch (title_art){
		case 1 :
			set_bkg_tiles(6, 5, heartWidth, heartHeight, heart);
			break;
		case 2 :
			set_bkg_tiles(5, 4, smileWidth, smileHeight, smile);
			break;
		case 3 :
			set_bkg_tiles(5, 4, skullWidth, skullHeight, skull);
			break;
	}
	text_print_string_bkg(4, 1, "SQUARE  FALL");
	text_print_string_bkg(4, 3, "PRESS  START");
	text_print_string_bkg(1, 16, "WIP FOR #GBCOMPO21");
	text_print_string_bkg(0, 17, "V 0.3 PARTY VERSION!");
	text_print_string_bkg(5, 14, "HI -");
	print_uint16_bkg(10, 14, hi_score, 5);
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