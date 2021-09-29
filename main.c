#include <gb/gb.h>

#include "lib/utils.h"
#include "tiles.c"

#include "title.h"
#include "game.h"
#include "gameover.h"

// declare globals here & in globals.h as extern!
uint16_t hi_score, score;
uint8_t title_art;

void main(void)
{
	DISPLAY_OFF;
	hi_score = 0;
	title_art = 1;
	set_bkg_data(0, 28, tiles_data);
	text_load_font();
	while(1) {
		run_title();
		run_game();
		run_gameover();
    }
}
