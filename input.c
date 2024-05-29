#include <ncurses.h>
#include "collections/dictionary.h"
#include "collections/dynarr.h"
#include "include/input.h"

DYNARR_HEADER(callback, input_event)
DYNARR(callback, input_event)

DICT_HEADER(events, cmd, callback_dynarr *, cmd, callbacks)
DICT(events, cmd, callback_dynarr *, cmd, callbacks)

static events_dict *dict;

void subscribe(cmd c, input_event x)
{
    callback_dynarr *arr = get_value_events_dict(dict, c);
    callback_dynarr_add_item(arr, x);
}

__attribute__((unused)) void unsubscribe(cmd c, input_event x)
{
    callback_dynarr *arr = get_value_events_dict(dict, c);
    callback_dynarr_remove_item(arr, x);
}

static void invoke(cmd c)
{
    callback_dynarr *arr = get_value_events_dict(dict, c);
    input_event func_addr;
    int i;

    for (i = 0; i < arr->count; ++i) {
        func_addr = (input_event) arr->array[i];
        func_addr();
    }
}

void update_input(void)
{
    int ch = getch();
    switch (ch) {
        case 'j':
            invoke(down);
            break;
        case 'k':
            invoke(up);
            break;
        case '\n':
            invoke(enter);
            break;
        default:
            break;
    }
}

void init_input(void)
{
    dict = create_events_dict();

    callback_dynarr *up_arr = create_callback_dynarr();
    add_to_events_dict(dict, up, up_arr);

    callback_dynarr *down_arr = create_callback_dynarr();
    add_to_events_dict(dict, down, down_arr);

    callback_dynarr *enter_arr = create_callback_dynarr();
    add_to_events_dict(dict, enter, enter_arr);
}