#include "../global/global.h"
#include "menus/include/menu.h"
#include "include/header.h"
#include "include/gui.h"

void draw_menu_path(void)
{
    const int line_y = 1;
    const int line_x = 2;
    int line_cursor;
    int name_size;
    Menu *menu;
    int i;

    line_cursor = line_x;
    clear_line(line_y, line_x);

    for (i = 0; i < menu_stack->count; i++) {
        menu = stack_menu_element_at(menu_stack, i);
        print(A_BOLD, menu->name, line_y, line_cursor);
        name_size = (int)strlen(menu->name);
        line_cursor += name_size;

        if(i + 1 < menu_stack->count)
            print(A_BOLD, ">", line_y, line_cursor++);
    }
}
