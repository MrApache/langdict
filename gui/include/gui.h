#pragma once
#include "../menus/include/menu.h"
#include "../../global/global.h"
#include "../../global/iristr.h"

extern WINDOW *main_win;
extern stack_menu *menu_stack;

point get_cursor(void);
void gui_clear(void);
void print(int attrb, string str, point pos);
void clear_line(int y, int x);
void set_active_menu(Menu *);

void init_gui(void);
void update_gui(void);
void draw_gui(void);
