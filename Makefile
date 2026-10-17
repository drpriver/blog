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

include posts.mak

.PHONY: all
all: $(PAGES)

# rss
feed.xml: $(PAGES)
	python3 do_rss.py
