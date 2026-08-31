#ifndef __COMMON_H__
#define __COMMON_H__

#include <string.h>
#include <graphx.h>
#include "gfx/gfx.h"
#include <ti/getcsc.h>
#include "states.h"
#include "dictionary_data.h"

extern void gfx_ScaledRLETSprite_NoClip(const gfx_rletsprite_t *sprite, int x, int y, uint8_t scale_x, uint8_t scale_y);
void gfx_PrintStringXYWrapped(const char *str, int x, int y, int max_width, int line_height);
const char *getDefinition(const word_entry_t *entry);

#endif // __COMMON_H__