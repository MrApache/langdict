#include "include/config.h"
#include "global/global.h"

int x_pos = 0;
int y_pos = 0;

void load_cfg()
{
    int row, col;
    getmaxyx(stdscr, row, col);

    x_pos = (col - GUI_COLS) / 2;
    y_pos = (row - GUI_LINES) / 2;
}
