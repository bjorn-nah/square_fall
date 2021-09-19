#include <gb/gb.h>
#include <stdint.h>
#include <rand.h>

#include "tiles.c"
#include "map.c"

// 0 - wihte
// 1 - black
// 2 - grey
UBYTE playground[] = {
	1,  1,  2,  2,  2,  2,  1,  1, 1,
	1,  2,  2,  2,  2,  2,  2,  1, 1,
	2,  2,  2,  2,  2,  2,  2,  2, 1,
	2,  2,  1,  2,  1,  2,  2,  2, 1,
	2,  2,  1,  2,  1,  2,  2,  2, 1,
	2,  2,  2,  1,  2,  2,  2,  1, 1,
	1,  2,  2,  2,  2,  2,  1,  1, 1,
	1,  2,  2,  2,  2,  2,  1,  1, 1,
	1,  2,  1,  2,  1,  2,  1,  1, 1
};

// functions declarations
void draw_xy(BYTE x, BYTE y, UBYTE color);
UBYTE get_color(BYTE x, BYTE y);
void set_color(BYTE x, BYTE y, UBYTE color);
uint8_t get_tile_ul(UBYTE square_color, UBYTE neighbour_color);
uint8_t get_tile_ur(UBYTE square_color, UBYTE neighbour_color);
uint8_t get_tile_dl(UBYTE square_color, UBYTE neighbour_color);
uint8_t get_tile_dr(UBYTE square_color, UBYTE neighbour_color);

// global variables

void run_game(void)
{
	uint8_t i, j;
	
	// load tiles data
	set_bkg_data(0, 16, tiles_data);
	// load map data
	set_bkg_tiles(0, 0, 20, 18, mergez);
	// Turns on the background layer
	SHOW_BKG;
	// Turns the display back on. 
	DISPLAY_ON;
	
	initrand(DIV_REG);
	
	//initialize vars
	i = 0;
	j = 0;
	
    // Loop forever
    while(1) {


		// Game main loop processing goes here
		draw_xy(i, j, get_color(i, j));
		//temp = rand() & 1;
		//draw_xy(i, j, temp + 1);
		i++;
		if(i>8){
			i = 0;
			j++;
		}
		if(j>8){
			for(i=0; i<9; i++){
				for(j=0; j<9; j++){
					playground[j*9+i] = (rand() & 1) + 1;
				}
			}
			i = 0;
			j = 0;
		}
		
		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}

void draw_xy(BYTE x, BYTE y, UBYTE color){
	UBYTE neighbour;
	uint8_t x_new, y_new;
	x_new = 1 + x + y;
	y_new = 8 - x + y;
	neighbour = get_color(x,  y-1);
	set_bkg_tile_xy(x_new, y_new, get_tile_ul(color, neighbour));
	neighbour = get_color(x+1,  y);
	set_bkg_tile_xy(x_new+1, y_new, get_tile_ur(color, neighbour));
	neighbour = get_color(x-1,  y);
	set_bkg_tile_xy(x_new, y_new+1, get_tile_dl(color, neighbour));
	neighbour = get_color(x,  y+1);
	set_bkg_tile_xy(x_new+1, y_new+1, get_tile_dr(color, neighbour));
}

UBYTE get_color(BYTE x, BYTE y){
	if((x >= 0 && x < 9) && (y >= 0 && y < 9)){
		return playground[y*9+x];
	}else{
		return 0;
	}
}

void set_color(BYTE x, BYTE y, UBYTE color){
	playground[y*9+x] = color;
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
		}
	}
	return 0;
}