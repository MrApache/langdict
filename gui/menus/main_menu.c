#include <string.h>
#include "include/menu.h"
#include "../../include/config.h"
#include "include/word_list.h"
#include "interaction/button.h"
#include "../include/gui.h"

#define WORD_MANAGER "Word manager"
#define PRACTICE_OPTION "Practice mode"
#define QUIT "Quit"

static Menu *main_menu;
static Menu *word_list;

static void enter_in_word_manager(void)
{
    set_active_menu(word_list);
}

static void enter_in_practice(void)
{
}

static void quit(void)
{
    endwin();
    exit_curses(0);
}

static void create_main_menu(void)
{
    int y = GUI_LINES / 2;
    int x = GUI_COLS / 2;

    int len_man = strlen(WORD_MANAGER);
    button *word_man = create_button(WORD_MANAGER, point(y, x - len_man / 2), point(1, len_man), (callback) enter_in_word_manager);

    int len_prac = strlen(PRACTICE_OPTION);
    button *prac_mode = create_button(PRACTICE_OPTION, point(y - 1, x - len_prac / 2), point(1, len_prac), (callback) enter_in_practice);

    int len_quit = strlen(QUIT);
    button *quit_btn = create_button(QUIT, point(y - 2, x - len_quit / 2), point(1, len_quit), (callback) quit);

    main_menu = create_menu("Menu", 3, word_man->base, prac_mode->base, quit_btn->base);
}

static void create_word_menu(void)
{
    word_list = get_word_list();
}

Menu *get_main_menu(void)
{
    if(main_menu == NULL)
    {
        create_main_menu();
        create_word_menu();
    }

    return main_menu;
}