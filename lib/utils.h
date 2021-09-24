#define TEXT_FONT_OFFSET 0xC0

#define _TEXT_CHAR_TOFU 0xFB
#define _TEXT_CHAR_0 TEXT_FONT_OFFSET + 0x10

extern void text_load_font();
extern void text_print_char_bkg(uint8_t x, uint8_t y, unsigned char chr);
extern void text_print_string_bkg(uint8_t x, uint8_t y, unsigned char *string);
extern void print_uint8_bkg(uint8_t x, uint8_t y, uint8_t var, uint8_t size);
extern void print_uint16_bkg(uint8_t x, uint8_t y, uint16_t var, uint8_t size);
extern void clear_bkg();