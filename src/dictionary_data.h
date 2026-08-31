#ifndef __DICTIONARY_DATA_H__
#define __DICTIONARY_DATA_H__

#include <stdint.h>

typedef struct
{
    const char *word;
    uint16_t sp_glyph_id;
    uint16_t def_offset;
} word_entry_t;

typedef struct
{
    int word_count;
    const word_entry_t *words;
    const char *def_string_table;
} dictionary_db_t;

extern const dictionary_db_t g_dictionary;

#endif // __DICTIONARY_DATA_H__