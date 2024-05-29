#include <locale.h>
#include "include/config.h"
#include "include/input.h"
#include "gui/include/gui.h"
#include "gui/include/header.h"
#include "gui/include/border.h"

void init_ncurses()
{
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
}

static void update_logic(void)
{
    update_input();
    update_gui();
}

static void draw(void)
{
    draw_menu_path();
    draw_gui();
}

static _Noreturn void loop()
{
    while (true) {
        update_logic();
        draw();
    }
}

int main() {
    init_ncurses();

    load_cfg();
    init_input();
    init_border();
    init_gui();

    loop();

    endwin();
    return 0;
}