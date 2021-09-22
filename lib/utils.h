#define TEXT_FONT_OFFSET 0xC0

#define _TEXT_CHAR_TOFU 0xFB

extern void text_load_font();
extern void text_print_char_bkg(uint8_t x, uint8_t y, unsigned char chr);
extern void text_print_string_bkg(uint8_t x, uint8_t y, unsigned char *string);