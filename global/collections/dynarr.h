#pragma once
#include <stdlib.h>

#define DEFAULT_SIZE 16
#define REALLOC_ERROR_NULL (-228)

#define DYNARR_HEADER(NAME, TYPE) \
typedef struct NAME##_dynarr \
{   \
    TYPE *array;   \
    int nextFree;   \
    int count;  \
    int size;   \
} NAME##_dynarr;   \
\
NAME##_dynarr *create_##NAME##_dynarr(void); \
void free_##NAME##_dynarr(NAME##_dynarr *); \
int NAME##_dynarr_contains_item(NAME##_dynarr *, TYPE); \
void NAME##_dynarr_add_item(NAME##_dynarr *, TYPE); \
int NAME##_dynarr_remove_item(NAME##_dynarr *, TYPE); \
void NAME##_dynarr_clear_arr(NAME##_dynarr *);

#define DYNARR(NAME, TYPE) \
NAME##_dynarr *create_##NAME##_dynarr(void) \
{ \
    NAME##_dynarr *arr = malloc(sizeof(NAME##_dynarr)); \
    arr->array = malloc(sizeof(TYPE) * DEFAULT_SIZE); \
    arr->count = 0; \
    arr->nextFree = 0; \
    arr->size = DEFAULT_SIZE; \
    return arr; \
}\
 \
void free_##NAME##_dynarr(NAME##_dynarr *arr) \
{\
    free(arr->array);\
    free(arr);\
} \
\
int NAME##_dynarr_contains_item(NAME##_dynarr *arr, TYPE item) \
{ \
    int result = 0; \
    TYPE element; \
\
    for (int i = 0; i < arr->count; ++i) { \
    element = arr->array[i]; \
    if(element == item) { \
        result = 1; \
        break; \
    } \
} \
 \
return result;\
} \
\
static void try_resize(NAME##_dynarr *arr)\
{ \
    if(arr->nextFree < arr->size - 1) \
        return; \
\
    void *temp_ptr = realloc(arr->array, arr->size * 2);\
    if(temp_ptr == NULL) \
        exit(REALLOC_ERROR_NULL); \
    arr->array = temp_ptr; \
    arr->size *= 2; \
} \
\
void NAME##_dynarr_add_item(NAME##_dynarr *arr, TYPE item) \
{ \
    try_resize(arr); \
    arr->array[arr->nextFree++] = item; \
    arr->count++; \
} \
 \
static void NAME##_dynarr_move_elements(NAME##_dynarr *arr, int start_index) \
{ \
    int prev_index = start_index; \
\
    for (int i = start_index + 1; i < arr->count; ++i) { \
        arr->array[prev_index] = arr->array[i]; \
        prev_index++; \
    } \
    arr->array[arr->count - 1] = NULL; \
    arr->count--; \
} \
\
int NAME##_dynarr_remove_item(NAME##_dynarr *arr, TYPE item) \
{ \
    int result = 0; \
    TYPE element; \
\
    for (int i = 0; i < arr->count; ++i) { \
        element = arr->array[i]; \
        if(element == item) { \
            arr->array[i] = NULL; \
            NAME##_dynarr_move_elements(arr, i); \
            result = 1; \
            break; \
        } \
    } \
 \
    return result; \
} \
\
void NAME##_dynarr_clear_arr(NAME##_dynarr *arr) \
{ \
    for (int i = arr->size - 1; i > -1; i--) { \
        arr->array[i] = NULL; \
    } \
    arr->count = 0; \
    arr->nextFree = 0; \
}
