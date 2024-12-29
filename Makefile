Depends: ; mkdir -p $@
Depends/build: ; mkdir -p $@
Depends/build/games: ; mkdir -p $@
docs: ; mkdir -p $@
build: ; mkdir -p $@
build/games: ; mkdir -p $@
docs/games: ; mkdir -p $@
include $(wildcard Depends/*.dep)
include $(wildcard Depends/build/*.dep)

docs/%.html: build/%.html | build docs docs/games build/games
	cp $< $@

# included makefiles will append to this
PAGES=docs/index.html docs/games/index.html

# index
build/index.html: index.dnd | Depends/build build
	dndc $< -o $@ -d Depends/$@
build/games/index.html: games-index.dnd | Depends/build/games build/games
	dndc $< -o $@ -d Depends/$@

docs/feed.xml: feed.xml | docs
	cp $< $@
docs/games/feed.xml: games-feed.xml | docs/games
	cp $< $@

.PHONY: clean
clean:
	rm -rf Depends
	rm -rf build
	rm -rf docs

.DEFAULT_GOAL:=all

# Templates in C
include ctemplates/ctemplates.mak

# run(**vars(args)) in python
include runvarsargs/runvarsargs.mak

# Type reification in C
include creification/creification.mak

# doctests in C
include cdoctest/cdoctest.mak

# compiling c to wasm
include c-in-wasm/c-in-wasm.mak

# implementing a hash table in C
include c-hash-table/c-hash-table.mak

# C macro reflection in D
include C-macro-reflection-in-D/C-macro-reflection-in-D.mak

# Use filters instead of macros
include vim-macros-overrated/vim-macros-overrated.mak

.PHONY: all
all: $(PAGES)

# rss
feed.xml: $(PAGES)
	python3 do_rss.py
