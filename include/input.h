#pragma once

typedef enum cmd
{
    up,
    down,
    enter,
} cmd;

typedef void (*input_event)(void);

void subscribe(cmd, input_event);

__attribute__((unused)) void unsubscribe(cmd, input_event);
void update_input(void);
void init_input(void);
