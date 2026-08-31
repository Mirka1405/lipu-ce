#include "common.h"

void gfx_ScaledRLETSprite_NoClip(const gfx_rletsprite_t *sprite, int x, int y, uint8_t scale_x, uint8_t scale_y)
{
    const uint8_t *data = sprite->data;
    uint8_t width = sprite->width;
    uint8_t height = sprite->height;

    for (uint8_t row = 0; row < height; row++)
    {
        uint8_t col = 0;
        int py = y + row * scale_y;

        while (col < width)
        {
            uint8_t skip = *data++;
            col += skip;

            if (col >= width)
                break;

            uint8_t count = *data++;
            uint8_t run_start_col = col;
            uint8_t i = 0;

            while (i < count)
            {
                uint8_t color = data[i];
                uint8_t run_len = 1;
                while (i + run_len < count && data[i + run_len] == color)
                {
                    run_len++;
                }

                gfx_SetColor(color);
                gfx_FillRectangle_NoClip(
                    x + (run_start_col + i) * scale_x,
                    py,
                    run_len * scale_x,
                    scale_y);

                i += run_len;
            }

            data += count;
            col += count;
        }
    }
}

void gfx_PrintStringXYWrapped(const char *str, int x, int y, int max_width, int line_height)
{
    gfx_SetTextXY(x, y);
    const char *word_start = str;
    const char *cursor = str;

    while (*cursor)
    {
        if (*cursor == ' ' || *cursor == '\n' || *(cursor + 1) == '\0')
        {
            size_t word_len = cursor - word_start;
            if (*(cursor + 1) == '\0' && *cursor != ' ' && *cursor != '\n')
            {
                word_len++;
            }

            char word_buf[64];
            if (word_len >= sizeof(word_buf))
                word_len = sizeof(word_buf) - 1;
            strncpy(word_buf, word_start, word_len);
            word_buf[word_len] = '\0';

            int word_width = gfx_GetStringWidth(word_buf);
            int space_width = gfx_GetCharWidth(' ');

            if (gfx_GetTextX() + word_width > x + max_width && gfx_GetTextX() > x)
                gfx_SetTextXY(x, gfx_GetTextY() + line_height);

            gfx_PrintString(word_buf);

            if (*cursor == ' ')
            {
                gfx_SetTextXY(gfx_GetTextX() + space_width, gfx_GetTextY());
            }
            else if (*cursor == '\n')
            {
                gfx_SetTextXY(x, gfx_GetTextY() + line_height);
            }

            word_start = cursor + 1;
        }
        cursor++;
    }
}

const char *getDefinition(const word_entry_t *entry)
{
    if (!entry)
        return NULL;
    return g_dictionary.def_string_table + entry->def_offset;
}