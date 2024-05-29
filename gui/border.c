#include "include/border.h"

cchar_t ul_corner, ur_corner, ll_corner, lr_corner, h_line, v_line;

void init_border(void)
{
    setcchar(&ul_corner, L"╭", A_NORMAL, 0, NULL);
    setcchar(&ur_corner, L"╮", A_NORMAL, 0, NULL);
    setcchar(&ll_corner, L"╰", A_NORMAL, 0, NULL);
    setcchar(&lr_corner, L"╯", A_NORMAL, 0, NULL);
    setcchar(&h_line, L"─", A_NORMAL, 0, NULL);
    setcchar(&v_line, L"│", A_NORMAL, 0, NULL);
}