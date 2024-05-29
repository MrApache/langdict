cmake_minimum_required(VERSION 3.27)
project(langdict C)

set(CMAKE_C_STANDARD 11)
set(CURSES_USE_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
set(ENV{TERM} "xterm-256color")

include_directories("global/" "gui/types")

add_executable(langdict main.c
        global/collections/dictionary.h
        gui/gui.c
        gui/include/gui.h
        gui/menus/menu.c
        gui/menus/include/menu.h
        global/iristr.h
        gui/menus/main_menu.c
        gui/menus/include/main_menu.h
        include/config.h
        config.c
        gui/menus/word_list.c
        gui/menus/include/word_list.h
        "global/collections/stack.h"
        input.c
        include/input.h
        include/input.h
        global/collections/dynarr.h
        gui/menus/add_word.c
        gui/menus/include/add_word.h
        gui/header.c
        gui/include/header.h
        gui/include/border.h
        gui/border.c
        global/global.h
        gui/types/interact.h
        gui/types/point.h
        gui/point.c
        gui/types/interaction/text_box.c
        gui/types/visual.h
        gui/types/interact.c
        gui/types/interaction/text_box.h
        gui/types/visual.c
        gui/types/interaction/button.c
        gui/types/interaction/button.h
        modes/text_input.c
        modes/text_input.h)

target_link_libraries(${PROJECT_NAME} ncurses)
