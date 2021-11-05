#include <gb/gb.h>

#include "lib/utils.h"
#include "tiles.c"

#include "cursor.c"

#include "title.h"
#include "menu.h"
#include "score_attack.h"
#include "puzzle.h"
#include "gameover.h"

#include "constants.h"

// declare globals here & in globals.h as extern!
uint16_t hi_score, score, game_mode;
uint8_t title_art;

void main(void)
{
	DISPLAY_OFF;
	hi_score = 0;
	title_art = 1;
	game_mode = SCORE;
	set_bkg_data(0, 28, tiles_data);
	text_load_font();
	
	// sprite load
	SPRITES_8x8;
    set_sprite_data(0, 1, cursor);
	set_sprite_tile(0, 0);
	
	while(1) {
		run_title();
		run_menu();
		if(game_mode == SCORE){
			run_score_attack();
		}
		if(game_mode == PUZZLE){
			run_puzzle();
		}
		run_gameover();
    }
}
