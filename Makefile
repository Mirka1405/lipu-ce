NAME = LIPUCE
DESCRIPTION = "lipu CE - toki pona dictionary"

ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

DEPS = $(SRCDIR)/dictionary_data.c

define EXTRA_CLEAN
	rm -f $(GFXDIR)/sitelen_pona_glyphs.png word_manifest.json $(SRCDIR)/dictionary_data.c
endef

include $(shell cedev-config --makefile)

gfx: $(GFXDIR)/sitelen_pona_glyphs.png

word_manifest.json:
	python3 tools/generate_manifest.py

$(SRCDIR)/dictionary_data.c: word_manifest.json
	python3 tools/generate_dictionary.py

$(GFXDIR)/sitelen_pona_glyphs.png: word_manifest.json
	python3 tools/generate_glyphs.py