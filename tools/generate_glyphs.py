#!/usr/bin/env python3
import json
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

MANIFEST_PATH = Path("word_manifest.json")

FONT_PATH = "tools/Fairfax.ttf"
OUTPUT_PATH = "src/gfx/sitelen_pona_glyphs.png"

GLYPH_WIDTH = 12
GLYPH_HEIGHT = 12

with open(MANIFEST_PATH) as f:
    words = json.load(f)
    
ucsur_chars = [chr(item["ucsur"]) for item in words]

def generate_glyphs():
    font = ImageFont.truetype(FONT_PATH, GLYPH_HEIGHT)
    atlas_width = GLYPH_WIDTH * len(ucsur_chars)
    
    atlas = Image.new('1', (atlas_width, GLYPH_HEIGHT), color=1)
    draw = ImageDraw.Draw(atlas)
    
    for i, code in enumerate(ucsur_chars):
        ox = i * GLYPH_WIDTH
        draw.text((ox, 0), code, font=font, fill=0)
    
    atlas.save(OUTPUT_PATH)
    print(f"Succesfully generated sitelen pona atlas from font {FONT_PATH}")
    
if __name__ == "__main__": generate_glyphs()