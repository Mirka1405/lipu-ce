NAME = LIPUCE
DESCRIPTION = "lipu CE - toki pona dictionary"

ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

DEPS = $(SRCDIR)/dictionary_data.c
EXTRA_C_SOURCES = $(SRCDIR)/dictionary_data.c

# add 'uncommon' and/or 'obscure' to include more words
WORD_CATEGORIES = core common

define EXTRA_CLEAN
	if [ -f src/gfx/convimg.yaml.lst ]; then \
		xargs -I{} rm -f $(GFXDIR)/{} < src/gfx/convimg.yaml.lst; \
	fi
	rm -f $(GFXDIR)/sitelen_pona_glyphs.png $(GFXDIR)/convimg.yaml.lst \
		word_manifest.json $(SRCDIR)/dictionary_data.c
endef

include $(shell cedev-config --makefile)

gfx: $(GFXDIR)/sitelen_pona_glyphs.png

word_manifest.json:
	WORD_CATEGORIES="$(WORD_CATEGORIES)" python3 tools/generate_manifest.py

$(SRCDIR)/dictionary_data.c: word_manifest.json
	python3 tools/generate_dictionary.py

$(GFXDIR)/sitelen_pona_glyphs.png: word_manifest.json
	python3 tools/generate_glyphs.py