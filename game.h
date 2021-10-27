#define WAIT 0

// cursor_state
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ACTION_A 5

// action_state
#define FALL_Y 6
#define FALL_X 7
#define FILL 8

// display_state
#define DISPLAY 9

#define NEW_BOMB_STEP 32
#define MAX_TULE_PER_SCREEN 32
#define VOID_TULE 255

extern void run_game();