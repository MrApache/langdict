#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include "include/word_list.h"
#include "../../include/config.h"
#include "include/add_word.h"

#define ADD_WORD "Add word"

static Menu *add_word(void)
{
    return get_add_word();
}

static Menu *remove_word(void)
{

}

Menu *get_word_list(void)
{
    int y = GUI_LINES / 2;
    int x = GUI_COLS / 2;

    Option *add_opt = opt_center(ADD_WORD, y, x, add_word, true);
    Menu *menu = create_menu("Word manager", 1, add_opt);
    return menu;
}
