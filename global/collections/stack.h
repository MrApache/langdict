//
// Created by irisu on 28.05.2024.
//
#pragma once
#include <stdlib.h>
#define DEFAULT_STACK_SIZE 16

#define STACK_HEADER(STACK_TYPE_NAME, TYPE) \
typedef struct STACK_TYPE_NAME           \
{                                        \
    TYPE *array;                         \
    int count;                           \
    int index;                              \
    int size;                                            \
}STACK_TYPE_NAME;                           \
STACK_TYPE_NAME *create_##STACK_TYPE_NAME(void);                                            \
void STACK_TYPE_NAME##_push(STACK_TYPE_NAME *stack, TYPE item); \
TYPE STACK_TYPE_NAME##_pop(STACK_TYPE_NAME *stack); \
TYPE STACK_TYPE_NAME##_element_at(STACK_TYPE_NAME *stack, int index);

#define Stack(STACK_TYPE_NAME, TYPE) \
STACK_TYPE_NAME *create_##STACK_TYPE_NAME(void)       \
{                                    \
    STACK_TYPE_NAME *stack = malloc(sizeof(STACK_TYPE_NAME)); \
    stack->array = malloc(sizeof(TYPE) * DEFAULT_STACK_SIZE); \
    stack->count = 0;                \
    stack->index = DEFAULT_STACK_SIZE - 1;                     \
    stack->size = DEFAULT_STACK_SIZE; \
    return stack;\
}\
void STACK_TYPE_NAME##_push(STACK_TYPE_NAME *stack, TYPE item) \
{                                    \
    stack->array[(stack->index)--] = item; \
    stack->count++;                                     \
}           \
TYPE STACK_TYPE_NAME##_pop(STACK_TYPE_NAME *stack)   \
{                                    \
    if(stack->count == 0) \
        return NULL; \
    TYPE item = stack->array[++(stack->index)]; \
    stack->count--; \
    return item; \
} \
TYPE STACK_TYPE_NAME##_element_at(STACK_TYPE_NAME *stack, int index) \
{ \
    if(stack->count == 0) \
        return NULL; \
    if(index > stack->count) \
        return NULL; \
    int arr_index = stack->size - 1; \
    if(arr_index < 0) \
        return NULL;  \
    TYPE item = stack->array[arr_index - index]; \
    return item; \
}
