#define GAME_QUIT_ITEM 2
#define GAME_STARTOVER_ITEM 1
#define O_TURN  1
#define X_TURN  0 
#define UD_BLANK 0
#define UD_X 1
#define UD_O 2

int turn;
Pixmap O_PIXMAP;
Pixmap X_PIXMAP;
Pixmap BLANK_PIXMAP;
GC gc;
Widget grid[3][3];
