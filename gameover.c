#include <gb/gb.h>

#include "lib/utils.h"
#include "lib/gbt_player.h"
#include "globals.h"

extern const unsigned char * song_gameover_Data[];

void run_gameover(void){
	uint8_t start;
	
	// init sound player
	disable_interrupts();
    gbt_play(song_gameover_Data, 1, 7);
    gbt_loop(0);
    set_interrupts(VBL_IFLAG);
    enable_interrupts();
	
	// init screen
	text_load_font();
	text_print_string_bkg(5, 7, "GAME  OVER");
	text_print_string_bkg(4, 9, "SCORE:");
	print_uint16_bkg(11, 9, score, 5);
	SHOW_BKG;
	DISPLAY_ON;
	start = 1;
	
	while(start){
		if(!joypad() && start==2) {
			start = 0;
		}
		if(joypad() & J_START) {
			start = 2;
		}
		wait_vbl_done();
		gbt_update();
	}
	gbt_stop();
	DISPLAY_OFF;
	HIDE_BKG;
	clear_bkg();
}