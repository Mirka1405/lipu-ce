#include "common.h"
#include "state_wordlist.h"

int main(void)
{
    gfx_Begin();

    // gfx config
    gfx_SetTextConfig(gfx_text_clip);
    gfx_SetTextTransparentColor(0xE0); // arbitrary unused color
    gfx_SetTextBGColor(0xE0);

    states_Init(&STATE_WORDLIST);

    while (!states_ShouldClose())
        states_Step();

    gfx_End();
    return 0;
}