#include "global.h"
#include "include/add_word.h"
#include "../../include/config.h"

#define WORD_LABEL "Word:"
#define TRANSLATION_LABEL "Translation:"

static Menu *add_word(void)
{

}

static Menu *remove_word(void)
{

}

Menu *get_add_word(void)
{
    int y = GUI_LINES / 2;
    int x = GUI_COLS / 2;

    Option *word_label = opt_center(WORD_LABEL, y, x, add_word, false);
    Menu *menu = create_menu("Add word", 1, word_label);
    return menu;
}