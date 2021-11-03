#include <gb/gb.h>
#include <stdint.h>
#include <rand.h>

#include "lib/gbt_player.h"
#include "map.c"
#include "cursor.c"

#include "constants.h"
#include "lib/game_commons.h"
#include "lib/utils.h"
#include "globals.h"

extern const unsigned char * song_game_Data[];

// global variables
uint8_t cursor_x, cursor_y, cursor_state, action_state, display_state, tics;
//uint8_t tiles_uppdated;
uint8_t bomb, next_bomb;
uint16_t new_bomb;

void run_game(void)
{
	// load map data
	set_bkg_tiles(0, 0, 20, 18, mergez);
	// Turns on the background layer
	SHOW_BKG;

	// init sound player
	disable_interrupts();
    gbt_play(song_game_Data, 1, 7);
    gbt_loop(1);
    set_interrupts(VBL_IFLAG);
    enable_interrupts();
	
	// init seed for random
	initrand(DIV_REG);
	
	//initialize vars
	cursor_x = 4;
	cursor_y = 4;
	cursor_state = WAIT;
	action_state = WAIT;
	display_state = DISPLAY;
	score = 0;
	bomb = 10;
	new_bomb = 64;
	next_bomb = 64;
	tics = 0;
	
	// sprite load
	SPRITES_8x8;
    set_sprite_data(0, 1, cursor);
	set_sprite_tile(0, 0);
	place_cursor(cursor_x, cursor_y);
	SHOW_SPRITES;
	
	// Turns the display back on. 
	DISPLAY_ON;
	
	text_print_string_bkg(14, 1, "SCORE");
	text_print_string_bkg(1, 15, "CHAIN");
	text_print_char_bkg(1, 1, '\\');
	text_print_string_bkg(1, 2, "NEXT");
	print_uint8_bkg(1, 16, 0, 2);	//combo
	print_uint8_bkg(2, 1, bomb, 2);
	print_uint16_bkg(14, 2, score, 5);
	print_uint8_bkg(1, 3, next_bomb, 2);
	
	init_playgrounds();
	
	while(display_state == DISPLAY){
		draw_all();
	}
	
	fade_in(50);
	
    // Loop forever
    while(bomb) {

		// if display_state == WAIT
		if(!display_state){
			
			physics_engine();
			
			if(tics){
				if(tics==1){
					// delete bouns on screen
					
					text_print_string_bkg(1, 2, "NEXT");
					print_uint8_bkg(1, 3, next_bomb, 2);
					text_print_string_bkg(3, 16, "   ");
				}
				tics--;
			}
			
			if(cursor_state == WAIT){
				if(joypad() & J_UP) {
					cursor_state = UP;
				}
				if(joypad() & J_DOWN) {
					cursor_state = DOWN;
				}
				if(joypad() & J_RIGHT) {
					cursor_state = RIGHT;
				}
				if(joypad() & J_LEFT) {
					cursor_state = LEFT;
				}
				move_cursor(cursor_x, cursor_y, cursor_state);
			}
			place_cursor(cursor_x, cursor_y);
			
			if(action_state == WAIT) {
				if(joypad() & J_A) {
					action_state = ACTION_A;
				}
			}
					
			// if no directions are pressed, resert cursor_state
			if(!(joypad() & 0x0FU) && action_state == WAIT){
				cursor_state = WAIT;
			}
		} 
		else{	// if display_state != WAIT
			draw_all();
		}

		
		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
		gbt_update();
    }
	if(score > hi_score){hi_score = score;}
	fade_out(50);
	title_art = rand_range();
	gbt_stop();
	clear_bkg();
	HIDE_SPRITES;
	DISPLAY_OFF;
	HIDE_BKG;
}

