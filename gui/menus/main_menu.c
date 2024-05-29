#include <string.h>
#include <ncurses.h>
#include "include/menu.h"
#include "../../include/config.h"
#include "include/word_list.h"

#define WORD_MANAGER "Word manager"
#define PRACTICE_OPTION "Practice mode"
#define QUIT "Quit"

static Menu *word_list;

static Menu *enter_in_word_manager(void)
{
    return word_list;
}

static Menu *enter_in_practice(void)
{
    return NULL;
}

static Menu *quit(void)
{
    endwin();
    exit_curses(0);
    return NULL;
}

Menu *get_main_menu(void)
{
    int y = GUI_LINES / 2;
    int x = GUI_COLS / 2;

    Option *add_option = opt_center(WORD_MANAGER, y, x, enter_in_word_manager, true);
    Option *practice_option = opt_center(PRACTICE_OPTION, y - 1, x, enter_in_practice, true);
    Option *quit_opt = opt_center(QUIT, y - 2, x, quit, true);

    Menu *menu = create_menu("Menu", 3, quit_opt, practice_option, add_option);
    word_list = get_word_list();
    return menu;
}