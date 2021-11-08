#include <gb/gb.h>
#include <stdint.h>
#include <rand.h>

#include "../constants.h"
#include "utils.h"
#include "game_vars.h"
#include "../globals.h"

// 0 - wihte
// 1 - black
// 2 - grey
// 3 - hard grey
UBYTE playground[] = {
	1,  1,  2,  2,  2,  2,  1,  1, 3,
	1,  2,  2,  2,  2,  2,  2,  1, 3,
	2,  2,  2,  2,  2,  2,  2,  2, 3,
	2,  2,  1,  2,  1,  2,  2,  2, 3,
	2,  2,  1,  2,  1,  2,  2,  2, 3,
	2,  2,  2,  1,  2,  2,  2,  1, 3,
	1,  2,  2,  2,  2,  2,  1,  1, 3,
	1,  2,  2,  2,  2,  2,  1,  1, 3,
	1,  2,  1,  2,  1,  2,  1,  1, 3
};

UBYTE playground_aff01[9*10] =  {0};
UBYTE playground_aff02[10*9] =  {0};

// local functions declarations
UBYTE get_color(BYTE x, BYTE y);
void set_color(BYTE x, BYTE y, UBYTE color);
uint8_t get_tile_ul(UBYTE square_color, UBYTE neighbour_color);
uint8_t get_tile_ur(UBYTE square_color, UBYTE neighbour_color);
uint8_t get_tile_dl(UBYTE square_color, UBYTE neighbour_color);
uint8_t get_tile_dr(UBYTE square_color, UBYTE neighbour_color);
void draw_aff01();
void draw_aff02();

void fill_all();
void fill_void();
uint8_t delete_zone(int x, int y);
uint8_t fall_y();
uint8_t fall_x();
uint8_t rand_range();

void load_playground(UBYTE *ground_rle);

UBYTE get_color(BYTE x, BYTE y){
	if((x >= 0 && x < 9) && (y >= 0 && y < 9)){
		return playground[y*9+x];
	}else{
		return 0;
	}
}

void set_color(BYTE x, BYTE y, UBYTE color){
	UBYTE neighbour;
	// enable display
	display_state = DISPLAY;
	
	playground[y*9+x] = color;
	neighbour = get_color(x,  y-1);
	playground_aff01[y*9+x] = get_tile_ul(color, neighbour);
	neighbour = get_color(x,  y+1);
	playground_aff01[(y+1)*9+x] =  get_tile_dr(color, neighbour);
	
	neighbour = get_color(x+1,  y);
	playground_aff02[y*10+x+1] = get_tile_ur(color, neighbour);
	neighbour = get_color(x-1,  y);
	playground_aff02[y*10+x] = get_tile_dl(color, neighbour);

}

// up - left
uint8_t get_tile_ul(UBYTE square_color, UBYTE neighbour_color){
	if (square_color == 0){
		switch (neighbour_color){
			case 0 :
				return 0;
			break;
			case 1 :
				return 7;
			break;
			case 2 :
				return 14;
			break;
			case 3 :
				return 19;
			break;
		}
	}
	if (square_color == 1){
		switch (neighbour_color){
			case 0 :
				return 6;
			break;
			case 1 :
				return 1;
			break;
			case 2 :
				return 10;
			break;
			case 3 :
				return 22;
			break;
		}
	}
	if (square_color == 2){
		switch (neighbour_color){
			case 0 :
				return 15;
			break;
			case 1 :
				return 11;
			break;
			case 2 :
				return 2;
			break;
			case 3 :
				return 26;
			break;
		}
	}
	if (square_color == 3){
		switch (neighbour_color){
			case 0 :
				return 18;
			break;
			case 1 :
				return 23;
			break;
			case 2 :
				return 27;
			break;
			case 3 :
				return 3;
			break;
		}
	}
	return 0;
}
// up - right
uint8_t get_tile_ur(UBYTE square_color, UBYTE neighbour_color){
	if (square_color == 0){
		switch (neighbour_color){
			case 0 :
				return 0;
			break;
			case 1 :
				return 5;
			break;
			case 2 :
				return 12;
			break;
			case 3 :
				return 3;
			break;
		}
	}
	if (square_color == 1){
		switch (neighbour_color){
			case 0 :
				return 4;
			break;
			case 1 :
				return 1;
			break;
			case 2 :
				return 8;
			break;
			case 3 :
				return 20;
			break;
		}
	}
	if (square_color == 2){
		switch (neighbour_color){
			case 0 :
				return 13;
			break;
			case 1 :
				return 9;
			break;
			case 2 :
				return 2;
			break;
			case 3 :
				return 24;
			break;
		}
	}
	if (square_color == 3){
		switch (neighbour_color){
			case 0 :
				return 16;
			break;
			case 1 :
				return 21;
			break;
			case 2 :
				return 25;
			break;
			case 3 :
				return 3;
			break;
		}
	}
	return 0;
}
// down - left
uint8_t get_tile_dl(UBYTE square_color, UBYTE neighbour_color){
	if (square_color == 0){
		switch (neighbour_color){
			case 0 :
				return 0;
			break;
			case 1 :
				return 4;
			break;
			case 2 :
				return 13;
			break;
			case 3 :
				return 16;
			break;
		}
	}
	if (square_color == 1){
		switch (neighbour_color){
			case 0 :
				return 5;
			break;
			case 1 :
				return 1;
			break;
			case 2 :
				return 9;
			break;
			case 3 :
				return 21;
			break;
		}
	}
	if (square_color == 2){
		switch (neighbour_color){
			case 0 :
				return 12;
			break;
			case 1 :
				return 8;
			break;
			case 2 :
				return 2;
			break;
			case 3 :
				return 25;
			break;
		}
	}
	if (square_color == 3){
		switch (neighbour_color){
			case 0 :
				return 17;
			break;
			case 1 :
				return 20;
			break;
			case 2 :
				return 24;
			break;
			case 3 :
				return 3;
			break;
		}
	}
	return 0;
}
// down - right
uint8_t get_tile_dr(UBYTE square_color, UBYTE neighbour_color){
	if (square_color == 0){
		switch (neighbour_color){
			case 0 :
				return 0;
			break;
			case 1 :
				return 6;
			break;
			case 2 :
				return 15;
			break;
			case 3 :
				return 18;
			break;
		}
	}
	if (square_color == 1){
		switch (neighbour_color){
			case 0 :
				return 7;
			break;
			case 1 :
				return 1;
			break;
			case 2 :
				return 11;
			break;
			case 3 :
				return 23;
			break;
		}
	}
	if (square_color == 2){
		switch (neighbour_color){
			case 0 :
				return 14;
			break;
			case 1 :
				return 10;
			break;
			case 2 :
				return 2;
			break;
			case 3 :
				return 27;
			break;
		}
	}
		if (square_color == 3){
		switch (neighbour_color){
			case 0 :
				return 19;
			break;
			case 1 :
				return 22;
			break;
			case 2 :
				return 26;
			break;
			case 3 :
				return 3;
			break;
		}
	}
	return 0;
}

void draw_all(){
	/*
	tiles_uppdated = 0;
	draw_aff01();
	draw_aff02();
	if(tiles_uppdated < MAX_TULE_PER_SCREEN){
		display_state = WAIT;
	}else{
		display_state = DISPLAY;
	}
	print_uint8_bkg(0, 0, tiles_uppdated, 3);
	*/
	draw_aff01();
	draw_aff02();
	display_state = WAIT;
}
void draw_aff01(){
	uint8_t x, y, x_new, y_new;
	for(x=0; x<9; x++){
		for(y=0; y<10; y++){
			if(playground_aff01[y*9+x]!=VOID_TULE){
				x_new = 1 + x + y;
				y_new = 8 - x + y;
				set_bkg_tile_xy(x_new, y_new, playground_aff01[y*9+x]);
				playground_aff01[y*9+x] = VOID_TULE;
				//tiles_uppdated++;
			}
		}
	}
}
void draw_aff02(){
	uint8_t x, y, x_new, y_new;
	for(x=0; x<10; x++){
		for(y=0; y<9; y++){
			if(playground_aff02[y*10+x]!=VOID_TULE){
				x_new = 1 + x + y;
				y_new = 9 - x + y;
				set_bkg_tile_xy(x_new, y_new, playground_aff02[y*10+x]);
				playground_aff02[y*10+x] = VOID_TULE;
				//tiles_uppdated++;
			}
		}
	}
}

// move the custor on the virtual playground
void move_cursor(int x, int y, uint8_t state){
	if(state == UP && y > 0){
		cursor_y--;
	}
	if(state == DOWN && y < 8){
		cursor_y++;
	}
	if(state == LEFT && x > 0){
		cursor_x--;
	}
	if(state == RIGHT && x < 8){
		cursor_x++;
	}
}

// place the custor on the real playground
void place_cursor(int x, int y){
	move_sprite(0, 20 + x*8 + y*8, 84 - x*8 + y*8);
}

void fill_all(){
	uint8_t i, j;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			set_color(i, j, rand_range());
		}
	}
}

void fill_void(){
	uint8_t i, j;
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(playground[j*9+i] == 0){
				set_color(i, j, rand_range());
			}
		}
	}
}

// I now recursiv function looks like a bad idea on Gameboy
// 
uint8_t delete_zone(int x, int y){
	UBYTE zone_color;
	uint8_t destroyed;
	destroyed = 1;
	zone_color = get_color(x, y);
	if(zone_color!=0){		// avoid infinite loop by reject the void deleting ;)
		set_color(x, y, 0);
		if(zone_color == get_color(x-1, y)){
			destroyed += delete_zone(x-1, y);
		}
		if(zone_color == get_color(x, y-1)){
			destroyed += delete_zone(x, y-1);
		}
		if(zone_color == get_color(x+1, y)){
			destroyed += delete_zone(x+1, y);
		}
		if(zone_color == get_color(x, y+1)){
			destroyed += delete_zone(x, y+1);
		}
	}
	return destroyed;
}

uint8_t fall_y(){
	uint8_t i, j, same;
	UBYTE square_color;
	same = 1;	// init return value to false
	for(j=8; j>0; j--){
		for(i=0; i<9; i++){
			if(get_color(i, j) == 0){
				square_color = get_color(i, j-1);
				if(square_color!=0){
					set_color(i, j, square_color);
					set_color(i, j-1, 0);
					same = 0;
				}
			}
		}
	}	
	return same;
}
uint8_t fall_x(){
	uint8_t i, j, same;
	UBYTE square_color;
	same = 1;	// init return value to false
	for(i=0; i<8; i++){
		for(j=0; j<9; j++){
			if(get_color(i, j) == 0){
				square_color = get_color(i+1, j);
				if(square_color!=0){
					set_color(i, j, square_color);
					set_color(i+1, j, 0);
					same = 0;
				}
			}
		}
	}
	return same;
}

void physics_engine(){
	uint8_t same, combo, bonus;
	if(action_state == FILL){
		fill_void();
		action_state = WAIT;
	}
	if(action_state == FALL_X){
		same = fall_x();
		if(same){
			action_state = FILL;
			bomb--;
			print_uint8_bkg(2, 1, bomb, 2);
		}
	}
	if(action_state == FALL_Y){
		same = fall_y();
		if(same){
			action_state = FALL_X;
		}
	}
	if(action_state == ACTION_A){
		combo = delete_zone(cursor_x,cursor_y);
		print_uint8_bkg(1, 16, combo, 2);
		bonus = combo / 8;
		score += combo + bonus;
		print_uint16_bkg(14, 2, score, 5);
		if(score >= new_bomb){
			new_bomb += NEW_BOMB_STEP;
			bomb++;
			tics = 60;
			text_print_string_bkg(1, 2, "NEW\\");
			text_print_string_bkg(1, 3, "  ");
		}
		next_bomb = new_bomb - score;
		if(!tics){
			text_print_string_bkg(1, 2, "NEXT");
			print_uint8_bkg(1, 3, next_bomb, 2);
		}
		if(bonus>0){
			text_print_char_bkg(3, 16, '+');
			print_uint8_bkg(4, 16, bonus, 2);
			tics = 60;
		}
		action_state = FALL_Y;
		
	}
}

void init_playgrounds(){
	fill_all();
}

uint8_t rand_range(){
	uint8_t res;
	res = 0;
	while(!res){
		res = rand() & 3;
	}
	return res;
}

void load_playground(UBYTE *ground_rle){
	uint8_t i, j, k, rle_iter, number, tile;
	i = 0;
	j = 0;
	rle_iter = 0;
	while(j<9){
		number = ground_rle[rle_iter];
		rle_iter++;
		tile = ground_rle[rle_iter];
		for(k = 0; k < number; k++){
			
			//playground[i] = tile;
			set_color(i,j,ground_rle[rle_iter]);
			i++;
			if(i==9){
				i=0;
				j++;
			}
			
		}		
		rle_iter++;		
	}
}