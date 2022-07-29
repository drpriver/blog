Depends: ; mkdir -p $@
Depends/build: ; mkdir -p $@
docs: ; mkdir -p $@
build: ; mkdir -p $@
include $(wildcard Depends/*.dep)
include $(wildcard Depends/build/*.dep)

docs/%.html: build/%.html | build docs
	cp $< $@

# included makefiles will append to this
PAGES=docs/index.html

# index
build/index.html: index.dnd | Depends/build build
	dndc $< -o $@ -d Depends/$@

# rss
feed.xml: $(PAGES)
	python3 do_rss.py

docs/feed.xml: feed.xml | docs
	cp $< $@

.PHONY: all
all: $(PAGES)


.PHONY: clean
clean:
	rm -rf Depends
	rm -rf build
	rm -rf docs

.DEFAULT_GOAL:=all

# ctemplates post
include ctemplates/ctemplates.mak

# run(**vars(args)) post
include runvarsargs/runvarsargs.mak
