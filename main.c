#include <stdint.h>

#include "title.h"
#include "game.h"
#include "gameover.h"

// declare globals here & in globals.h as extern!
uint16_t hi_score, score;

void main(void)
{
	hi_score = 0;
	while(1) {
		run_title();
		run_game();
		run_gameover();
    }
}
