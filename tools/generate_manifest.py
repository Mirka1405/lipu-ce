#!/usr/bin/env python3
import json
import tomllib
from pathlib import Path

OUTPUT_PATH = Path("word_manifest.json")

SONA_DIR = Path("sona")
WORDS_META_DIR = SONA_DIR / "words" / "metadata"
DEFINITIONS_FILE = SONA_DIR / "words" / "source" / "definitions.toml"

def generate_manifest():
    with open(DEFINITIONS_FILE, "rb") as f:
        definitions = tomllib.load(f)
    
    manifest = []
    
    for meta_file in sorted(WORDS_META_DIR.glob("*.toml")):
        word_key = meta_file.stem
        
        with open(meta_file, "rb") as f:
            meta = tomllib.load(f)
        
        ucsur_hex = meta.get("representations").get("ucsur")
        if not ucsur_hex: continue
        
        codepoint = int(ucsur_hex.replace("U+", ""), 16)
        
        manifest.append({
            "word": word_key,
            "ucsur": codepoint,
            "definition": definitions.get(word_key, ""),
            "category": meta.get("usage_category", "obscure")
        })
    
    with open(OUTPUT_PATH, "w", encoding="utf-8") as f:
        json.dump(manifest, f, indent=4, ensure_ascii=False)
    
    print(f"Generated master word manifest with {len(manifest)} words")

if __name__ == "__main__": generate_manifest()