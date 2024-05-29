#pragma once
#include <stdlib.h>

#define DEFAULT_CAPACITY 16

#define DICT_HEADER(DICT_TYPE_NAME, KEY_TYPE, VALUE_TYPE, KEY_COL_NAME, VALUE_COL_NAME) \
    typedef struct DICT_TYPE_NAME##_pair \
    { \
        KEY_TYPE key; \
        VALUE_TYPE value; \
    } DICT_TYPE_NAME##_pair; \
    typedef struct KEY_COL_NAME##_collection \
    {\
        KEY_TYPE *array;\
    } KEY_COL_NAME##_collection;\
    typedef struct VALUE_COL_NAME##_collection \
    {\
        VALUE_TYPE *array;\
    } VALUE_COL_NAME##_collection;\
    \
    typedef struct DICT_TYPE_NAME##_dict \
    { \
        KEY_COL_NAME##_collection * const keys; \
        VALUE_COL_NAME##_collection * const values; \
        DICT_TYPE_NAME##_pair *pairs; \
        size_t count; \
        size_t capacity; \
    } DICT_TYPE_NAME##_dict;                              \
    DICT_TYPE_NAME##_dict *create_##DICT_TYPE_NAME##_dict(void); \
    int contains_key_##KEY_TYPE(const DICT_TYPE_NAME##_dict *dict, const KEY_TYPE key); \
    int add_to_##DICT_TYPE_NAME##_dict(DICT_TYPE_NAME##_dict *dict, const KEY_TYPE key, VALUE_TYPE value); \
    VALUE_TYPE get_value_##DICT_TYPE_NAME##_dict(const DICT_TYPE_NAME##_dict *dict, const KEY_TYPE key); \
    int remove_key_##DICT_TYPE_NAME##_dict(DICT_TYPE_NAME##_dict *dict, const KEY_TYPE key);

#define DICT(DICT_TYPE_NAME, KEY_TYPE, VALUE_TYPE, KEY_COL_NAME, VALUE_COL_NAME) \
DICT_TYPE_NAME##_dict *create_##DICT_TYPE_NAME##_dict(void) { \
    DICT_TYPE_NAME##_dict *dict = malloc(sizeof(DICT_TYPE_NAME##_dict));         \
    KEY_COL_NAME##_collection *keys = malloc(sizeof(KEY_COL_NAME##_collection)); \
    VALUE_COL_NAME##_collection *values = malloc(sizeof(VALUE_COL_NAME##_collection)); \
                                                                                 \
    *((KEY_COL_NAME##_collection **)&dict->keys) = keys; \
    *((VALUE_COL_NAME##_collection **)&dict->values) = values;               \
    dict->keys->array = malloc(sizeof(KEY_TYPE) * DEFAULT_CAPACITY); \
    dict->values->array = malloc(sizeof(KEY_TYPE) * DEFAULT_CAPACITY); \
 \
    dict->pairs = malloc(sizeof(DICT_TYPE_NAME##_pair) * DEFAULT_CAPACITY); \
    dict->capacity = DEFAULT_CAPACITY; \
    return dict; \
} \
\
int contains_key_##KEY_TYPE(const DICT_TYPE_NAME##_dict *dict, const KEY_TYPE key) \
{ \
    DICT_TYPE_NAME##_pair element; \
    size_t count = dict->count; \
\
    for (int i = 0; i < count; ++i) { \
        element = dict->pairs[i]; \
        if(element.key == key) \
            return 1; \
    } \
\
    return 0; \
} \
\
static void resize_if_can(DICT_TYPE_NAME##_dict *dict) \
{ \
    if(dict->count != dict->capacity) \
        return; \
    \
    dict->capacity *= 2; \
\
    KEY_TYPE *keys_ptr = (KEY_TYPE *)realloc(dict->keys->array, sizeof(KEY_TYPE) * dict->capacity); \
    if(keys_ptr != NULL) \
        dict->keys->array = keys_ptr; \
\
    VALUE_TYPE *value_ptr = (VALUE_TYPE *)realloc(dict->values->array, sizeof(VALUE_TYPE) * dict->capacity); \
    if(value_ptr != NULL) \
        dict->values->array = value_ptr; \
\
    DICT_TYPE_NAME##_pair *array = malloc(sizeof(DICT_TYPE_NAME##_pair) * dict->capacity); \
    memmove(array, dict->pairs, dict->count * sizeof(DICT_TYPE_NAME##_pair)); \
    free(dict->pairs); \
    dict->pairs = array; \
} \
\
int add_to_##DICT_TYPE_NAME##_dict(DICT_TYPE_NAME##_dict *dict, const KEY_TYPE key, VALUE_TYPE value) \
{ \
    if(contains_key_##KEY_TYPE(dict, key)) \
        return 0; \
    DICT_TYPE_NAME##_pair element; \
    element.key = key; \
    element.value = value; \
\
    resize_if_can(dict); \
\
    dict->keys->array[dict->count] = key; \
    dict->values->array[dict->count] = value; \
    dict->pairs[dict->count++] = element; \
    return 1; \
}\
VALUE_TYPE get_value_##DICT_TYPE_NAME##_dict(const DICT_TYPE_NAME##_dict *dict, const KEY_TYPE key) \
{ \
    DICT_TYPE_NAME##_pair element; \
    size_t count = dict->count; \
\
    for (int i = 0; i < count; ++i) { \
        element = dict->pairs[i]; \
        if(element.key == key) \
        return element.value; \
    } \
 \
    return NULL; \
} \
\
static void move_elements(DICT_TYPE_NAME##_dict *dict, int start_index) \
{ \
    const DICT_TYPE_NAME##_pair empty_elem = {}; \
    int prev_index = start_index; \
   \
    for (int i = start_index + 1; i < dict->count; ++i) { \
        dict->pairs[prev_index] = dict->pairs[i]; \
        dict->keys->array[prev_index] = dict->keys->array[i]; \
        dict->values->array[prev_index] = dict->values->array[i]; \
        prev_index++; \
    } \
    dict->pairs[dict->count - 1] = empty_elem; \
    dict->count--; \
} \
\
int remove_key_##DICT_TYPE_NAME##_dict(DICT_TYPE_NAME##_dict *dict, const KEY_TYPE key) \
{ \
    if(!contains_key_##KEY_TYPE(dict, key)) \
        return 0; \
\
    DICT_TYPE_NAME##_pair element; \
    size_t count = dict->count; \
\
    for (int i = 0; i < count; ++i) { \
        element = dict->pairs[i]; \
        if(element.key == key) { \
            move_elements(dict, i); \
            break; \
        } \
    } \
 \
    return 1; \
}
/*
*/
/*
typedef struct Word
{
    const char *key;
    char *value;

} Word;
*/

/*
typedef struct KeyCollection
{
    const char **array;

} KeyCollection;
*/

/*
typedef struct ValueCollection
{
    char **array;

} ValueCollection;
*/

/*
typedef struct Dictionary
{
    KeyCollection * const keys;
    ValueCollection * const values;
    Word *words;
    size_t count;
    size_t capacity;

} Dictionary;
*/
#include "../iristr.h"
DICT_HEADER(word, string, string, key_str, val_str)
