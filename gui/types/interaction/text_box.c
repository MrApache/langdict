#include <malloc.h>
#include "global.h"
#include "text_box.h"

static void draw(print_func print, const void *src)
{
    const text_box *tb;
    size_t label_len, buff_size;
    point tb_pos, label_pos;

    tb = (text_box *)src;
    tb_pos = tb->base->position;
    label_len = strlen(tb->base->name);

    buff_size = label_len + tb->base->interaction.size.x;
    char buff[buff_size];
    memset(buff, SPACE_CHAR, sizeof(char) * buff_size);
    memcpy(buff, tb->base->name, sizeof(char) * label_len);

    label_pos = point(tb_pos.y, tb_pos.x - label_len);
    print(A_NORMAL, buff, label_pos);
}

text_box *create_text_box(string label, point pos, point intSize, callback cb)
{
    text_box *tb = malloc(sizeof(text_box));
    interact in = {true, pos, intSize, cb};
    visual *vis = create_visual(label, pos, in, create_draw_data(draw, tb));
    tb->base = vis;
    return tb;
}

void free_text_box(text_box *tb)
{
    free(tb->base);
    free(tb);
}