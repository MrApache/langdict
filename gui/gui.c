#include <string.h>
#include "menus/include/menu.h"
#include "include/gui.h"
#include "menus/include/main_menu.h"
#include "../include/config.h"
#include "../include/input.h"
#include "collections/dynarr.h"
#include "include/border.h"
#include "interaction/button.h"

#define BACK_OPT "Back"
DYNARR_HEADER(vis, visual *)
DYNARR(vis, visual *)

WINDOW *main_win;
stack_menu *menu_stack;

static Menu *active_menu;

static int selection_index;
static button *back_opt;
static vis_dynarr *visuals;

point get_cursor(void)
{
    int y = getcury(main_win);
    int x = getcurx(main_win);
    return point(y, x);
}

void gui_clear(void)
{
    wclear(main_win);
    wborder_set(main_win, &v_line, &v_line, &h_line, &h_line, &ul_corner, &ur_corner, &ll_corner, &lr_corner);
    wrefresh(main_win);
}

void print(int attrb, string str, point pos)
{
    wattron(main_win, attrb);
    mvwprintw(main_win, pos.y, pos.x, "%s", str);
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
    draw_data draw;
    visual *vis;
    int i;

    for (i = 0; i < active_menu->opt_count; ++i) {
        vis = active_menu->options[i];
        draw = vis->draw;
        draw.func(print, draw.source);
    }

    if(menu_stack->count <= 1)
        return;

    vis = back_opt->base;
    draw = vis->draw;
    draw.func(print, draw.source);
}

void set_active_menu(Menu *menu)
{
    visual *vis;
    int i;

    vis_dynarr_clear_arr(visuals);
    stack_menu_push(menu_stack, menu);
    active_menu = menu;

    if(menu_stack->count > 1)
        vis_dynarr_add_item(visuals, back_opt->base);

    for (i = 0; i < active_menu->opt_count; ++i) {
        vis = active_menu->options[i];
        if(vis->interaction.interactable)
            vis_dynarr_add_item(visuals, active_menu->options[i]);
    }
}

static void clamp(void)
{
    if(selection_index < 0)
        selection_index = 0;

    if(selection_index >= visuals->count)
        selection_index = visuals->count - 1;
}

static void go_back(void)
{
    stack_menu_pop(menu_stack); //ignore current menu
    set_active_menu(stack_menu_pop(menu_stack)); //return previous
}

void invoke(void)
{
    visual *vis = visuals->array[selection_index];
    vis->interaction.callback();
    gui_clear();
}

void update_gui(void)
{
    clamp();
}

static void draw_selected_option(void)
{
    const visual *vis;
    int x_size, x;
    interact in;
    char ch;

    vis = visuals->array[selection_index];
    in = vis->interaction;
    x_size = in.size.x;

    char buff[x_size + 1];
    buff[x_size] = NULL_CHR;

    for (x = 0; x < x_size; ++x) {
        ch = mvwinch(main_win, in.position.y, in.position.x + x) & A_CHARTEXT;
        buff[x] = ch;
    }

    print(A_STANDOUT, buff, point(in.position.y, in.position.x));
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
    point pos = point(y, x);
    point size = point(1, strlen(BACK_OPT));
    back_opt = create_button(BACK_OPT, pos, size, go_back);
}

static void on_up(void)
{
    selection_index++;
    clamp();
}

static void on_down(void)
{
    selection_index--;
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

    visuals = create_vis_dynarr();
    create_back_option();
    menu_stack = create_stack_menu();
    set_active_menu(get_main_menu());
    input_subscribe();
}