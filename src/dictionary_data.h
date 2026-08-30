#ifndef DICTIONARY_DATA_H
#define DICTIONARY_DATA_H

#include <stdint.h>

typedef struct
{
    const char *word;
    uint16_t sp_glyph_id;
    uint16_t def_offset;
} word_entry_t;

typedef struct
{
    uint16_t word_count;
    const word_entry_t *words;
    const char *def_string_table;
} dictionary_db_t;

extern const dictionary_db_t g_dictionary;

#endif
