// extern functions declarations
extern void draw_all();
extern void move_cursor(int x, int y, uint8_t state);
extern void place_cursor(int x, int y);
extern void physics_engine();
extern void physics_puzzle();
extern void init_playgrounds();
extern uint8_t rand_range();
extern void load_playground(UBYTE *ground_rle);