#include "state_wordlist.h"

#define WORD_LIST_START_Y 25
#define WORD_BOX_HEIGHT 40
#define BOX_MARGIN 5
#define MAX_WORDS_SHOWN 5

static uint8_t pressed_key = 0;

static int selected_word = 0;
static int wordlist_start_idx = 0;

void selectNextWord()
{
    selected_word++;
    if (selected_word >= g_dictionary.word_count)
        selected_word = g_dictionary.word_count - 1;
    if (selected_word >= wordlist_start_idx + MAX_WORDS_SHOWN)
        wordlist_start_idx++;
}

void selectPrevWord()
{
    selected_word--;
    if (selected_word < 0)
        selected_word = 0;
    if (selected_word < wordlist_start_idx)
        wordlist_start_idx--;
}

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

void DrawWordInfo(const word_entry_t *word, int y, bool selected)
{
    // box
    if (selected)
        gfx_SetColor(0x4A);
    else
        gfx_SetColor(0xB5);
    gfx_Rectangle(BOX_MARGIN, y + BOX_MARGIN, GFX_LCD_WIDTH - BOX_MARGIN * 2, WORD_BOX_HEIGHT - BOX_MARGIN);

    // sitelen pona
    gfx_ScaledRLETSprite_NoClip(sitelen_pona_glyphs_tiles[word->sp_glyph_id], 10, y + 12, 2, 2);

    // sitelen Lasina
    gfx_SetTextFGColor(0x00);
    gfx_PrintStringXY(word->word, 40, y + 18);
}

void step(void)
{
    if ((pressed_key = os_GetCSC()))
    {
        switch (pressed_key)
        {
        case sk_Clear:
            states_EnterState(NULL);
            break;
        case sk_Down:
            selectNextWord();
            break;
        case sk_Up:
            selectPrevWord();
            break;
        default:
            break;
        }
    }
}

void draw(void)
{
    gfx_SetDraw(gfx_buffer);
    gfx_FillScreen(0xFF);

    // draw top bar
    gfx_SetColor(0x4A);
    gfx_FillRectangle_NoClip(0, 0, GFX_LCD_WIDTH, 20);
    gfx_SetTextFGColor(0xFF);
    gfx_PrintStringXY("lipu CE", 5, 5);

    // draw word list
    for (int i = 0; i < 5; i++)
    {
        int y = WORD_LIST_START_Y + (WORD_BOX_HEIGHT + 2) * i;
        DrawWordInfo(&g_dictionary.words[wordlist_start_idx + i], y, wordlist_start_idx + i == selected_word);
    }

    gfx_Blit(gfx_buffer);
}

const game_state_t STATE_WORDLIST = {NULL, step, draw, NULL};