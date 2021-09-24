#include <gb/gb.h>

#include "utils.h"
#include "font.h"

// text functions adapted from https://github.com/flozz/gameboy-examples/tree/master/11-custom-text
void text_load_font() {
	set_bkg_data(TEXT_FONT_OFFSET, FONT_TILESET_TILE_COUNT, FONT_TILESET);
}
void text_print_char_bkg(uint8_t x, uint8_t y, unsigned char chr){
	uint8_t tile = _TEXT_CHAR_TOFU;
	
	if (chr >= ' ' && chr <= '`'){
		tile = TEXT_FONT_OFFSET + chr - ' ';
	}
	set_bkg_tiles(x, y, 1, 1, &tile);
}
void text_print_string_bkg(uint8_t x, uint8_t y, unsigned char *string) {
	uint8_t offset_x = 0;
    uint8_t offset_y = 0;
    while (string[0]) {
        if (string[0] == '\n') {
            offset_x = 0; 
            offset_y += 1;
        } else {
            text_print_char_bkg(x + offset_x, y + offset_y, (unsigned char) string[0]);
            offset_x += 1;
        }
        string += 1;
    }
}

void print_uint8_bkg(uint8_t x, uint8_t y, uint8_t var, uint8_t size){
	uint8_t i, print, tile;
	for(i=1; i<=size; i++){
		print = var % 10;
		tile = _TEXT_CHAR_0 + print;
		set_bkg_tiles(x+size-i, y, 1, 1, &tile);
		var = var/10;
	}
}
void print_uint16_bkg(uint8_t x, uint8_t y, uint16_t var, uint8_t size){
	uint8_t i, tile;
	for(i=1; i<=size; i++){
		tile = _TEXT_CHAR_0 + var % 10;
		set_bkg_tiles(x+size-i, y, 1, 1, &tile);
		var = var/10;
	}
}

void clear_bkg(){
	uint8_t i, j, tile;
	tile = 0;
	for(i=0; i<20; i++){
		for(j=0; j<18; j++){
			set_bkg_tiles(i, j, 1, 1, &tile);
		}
	}
}