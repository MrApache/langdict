#include "global.h"
#include "include/add_word.h"
#include "../../include/config.h"
#include "interaction/text_box.h"
#include "../modes/text_input.h"

#define WORD_LABEL "Word:"
#define TRANSLATION_LABEL "Translation:"

static void add_word(void)
{
    enable_text_input();
}

Menu *get_add_word(void)
{
    int y = GUI_LINES / 2;
    int x = GUI_COLS / 2;
    point pos = point(y, x - 8);
    point size = point(y, 16);

    text_box *tb = create_text_box(WORD_LABEL, pos, size, add_word);
    Menu *menu = create_menu("Add word", 1, tb->base);
    return menu;
}