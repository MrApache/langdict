#include <stdbool.h>
#include "text_input.h"
#include "global.h"
#include "../gui/include/gui.h"

string enable_text_input(void)
{
    draw_gui();
    const int buff_size = 12;

    char ch;
    char buff[buff_size];
    int buff_index = 0;
    point cur_pos = get_cursor();
    memset(buff, SPACE_CHAR, sizeof(char) * buff_size);

    print(A_NORMAL, buff, cur_pos);

    while((ch = getch() != '\n')) {
        if(buff_index + 1 >= buff_size)
            break;

        buff[buff_index++] = ch;
        print(A_NORMAL, buff, cur_pos);
    }

    size_t result_size = sizeof(char) * buff_index;
    char *result = malloc(result_size);
    memcpy(result, buff, result_size);
    return result;
}