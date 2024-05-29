#include <string.h>
#include "menus/include/menu.h"
#include "include/gui.h"
#include "menus/include/main_menu.h"
#include "../include/config.h"
#include "../include/input.h"
#include "collections/dynarr.h"
#include "include/border.h"

#define BACK_OPT "Back"
DYNARR_HEADER(opt, Option *)
DYNARR(opt, Option *)

WINDOW *main_win;
stack_menu *menu_stack;

static Menu *active_menu;

static int selection_index;
static Option *back_opt;
static opt_dynarr *options;

void gui_clear(void)
{
    wclear(main_win);
    wborder_set(main_win, &v_line, &v_line, &h_line, &h_line, &ul_corner, &ur_corner, &ll_corner, &lr_corner);
    wrefresh(main_win);
}

void print(int attrb, string str, int y, int x)
{
    wattron(main_win, attrb);
    mvwprintw(main_win, y, x, "%s", str);
    wattroff(main_win, attrb);
    wrefresh(main_win);
}

void clear_line(int y, int x)
{
    mvwprintw(main_win, y, x, EMPTY_STR);
    wclrtoeol(main_win);
    wborder_set(main_win, &v_line, &v_line, &h_line, &h_line, &ul_corner, &ur_corner, &ll_corner, &lr_corner);
    wrefresh(main_win);
}

void draw_active_menu(void)
{
    Option *opt;
    int i;

    for (i = 0; i < active_menu->opt_count; ++i) {
        opt = active_menu->options[i];
        mvwaddstr(main_win, opt->y, opt->x, opt->name);
    }
/*
    for (i = 0; i < options->count; ++i) {
        opt = options->array[i];
        mvwaddstr(main_win, opt->y, opt->x, opt->name);
    }
*/
}

static void clamp(void)
{
    if(selection_index < 0)
        selection_index = 0;

    if(selection_index >= options->count)
        selection_index = options->count - 1;
}

void set_active_menu(Menu *menu)
{
    Option *opt;
    opt_dynarr_clear_arr(options);
    stack_menu_push(menu_stack, menu);
    active_menu = menu;
    for (int i = 0; i < active_menu->opt_count; ++i) {
        opt = active_menu->options[i];
        if(opt->interactable)
            opt_dynarr_add_item(options, active_menu->options[i]);
    }

    if(menu_stack->count > 1)
        opt_dynarr_add_item(options, back_opt);
}

Menu *go_back(void)
{
    stack_menu_pop(menu_stack); //ignore current menu
    return stack_menu_pop(menu_stack); //return previous
}

void invoke(void)
{
    Option *option = options->array[selection_index];
    set_active_menu(invoke_opt(option));
    gui_clear();
}

void update_gui(void)
{
    clamp();
}

static void draw_selected_option(void)
{
    Option *option = options->array[selection_index];
    print(A_STANDOUT, option->name, option->y, option->x);
}

void draw_gui(void)
{
    draw_active_menu();
    draw_selected_option();
    wrefresh(main_win);
}

static void create_back_option(void)
{
    const int y = GUI_LINES - 2;
    const int x = GUI_COLS / 2 - strlen(BACK_OPT) / 2;
    back_opt = create_option(BACK_OPT, y, x, (callback) go_back, true);
}

static void on_up(void)
{
    selection_index--;
    clamp();
}

static void on_down(void)
{
    selection_index++;
    clamp();
}

static void on_enter(void)
{
    invoke();
}

static void input_subscribe(void)
{
    subscribe(up, on_up);
    subscribe(down, on_down);
    subscribe(enter, on_enter);
}

void init_gui(void)
{
    main_win = newwin(GUI_LINES, GUI_COLS, y_pos, x_pos);
    wborder_set(main_win, &v_line, &v_line, &h_line, &h_line, &ul_corner, &ur_corner, &ll_corner, &lr_corner);
    wrefresh(main_win);

    options = create_opt_dynarr();
    create_back_option();
    menu_stack = create_stack_menu();
    set_active_menu(get_main_menu());
    input_subscribe();
}