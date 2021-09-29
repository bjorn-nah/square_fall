#define TEXT_FONT_OFFSET 0xC0

#define _TEXT_CHAR_TOFU 0xFB
#define _TEXT_CHAR_0 TEXT_FONT_OFFSET + 0x10

#define WHITE  0x00
#define SILVER 0x01
#define GRAY   0x02
#define BLACK  0x03
#define PALETTE(c0, c1, c2, c3) c0 | c1 << 2 | c2 << 4 | c3 << 6

extern void text_load_font();
extern void text_print_char_bkg(uint8_t x, uint8_t y, unsigned char chr);
extern void text_print_string_bkg(uint8_t x, uint8_t y, unsigned char *string);
extern void print_uint8_bkg(uint8_t x, uint8_t y, uint8_t var, uint8_t size);
extern void print_uint16_bkg(uint8_t x, uint8_t y, uint16_t var, uint8_t size);
extern void clear_bkg();
extern void fade_in(uint16_t fade_delay);
extern void fade_out(uint16_t fade_delay);
extern void fade_set();
extern void fade_reset();