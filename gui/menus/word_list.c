#include <string.h>
#include "include/word_list.h"
#include "../../include/config.h"
#include "interaction/button.h"
#include "../include/gui.h"
#include "include/add_word.h"

#define ADD_WORD "Add word"
#define RM_WORD "Remove word"

#define Y (GUI_LINES / 2)
#define X (GUI_COLS /2)

static Menu *word_list_menu;
static Menu *add_word_menu;
static Menu *rm_word_menu;

static void add_word(void)
{
    set_active_menu(add_word_menu);
}

static void remove_word(void)
{
    set_active_menu(rm_word_menu);
}

static void create_word_list_menu(void)
{
    int len_add = strlen(ADD_WORD);
    button *add_btn = create_button(ADD_WORD, point(Y, X - len_add / 2), point(1, len_add), (callback) add_word);

    int len_rm = strlen(RM_WORD);
    button *rm_btn = create_button(RM_WORD, point(Y - 1, X - len_rm / 2), point(1, len_rm), (callback) remove_word);

    word_list_menu = create_menu("Word manager", 2, add_btn->base, rm_btn->base);
}

static void create_add_word_menu(void)
{
    add_word_menu = get_add_word();
}

static void create_rm_word_menu(void)
{
}

Menu *get_word_list(void)
{
    if(word_list_menu == NULL)
    {
        create_word_list_menu();
        create_add_word_menu();
        create_rm_word_menu();
    }

    return word_list_menu;
}
