Depends: ; mkdir -p $@
Depends/build: ; mkdir -p $@
docs: ; mkdir -p $@
build: ; mkdir -p $@
include $(wildcard Depends/*.dep)
include $(wildcard Depends/build/*.dep)

docs/%.html: build/%.html | build docs
	cp $< $@

# ctemplates post

build/ctemplates: ; mkdir -p $@

build/ctemplates/%.c.html: ctemplates/%.c | build/ctemplates
	python3 -m cdoc $< -o $@
build/ctemplates/%.h.html: ctemplates/%.h | build/ctemplates
	python3 -m cdoc $< -o $@
build/ctemplates/darray.h.html: ctemplates/darray.h | build/ctemplates
	python3 -m cdoc $< -o $@ --cflags -DDARRAY_T=int
build/ctemplates.html: ctemplates/ctemplates.dnd | build Depends/build
	dndc $< -o $@ -d Depends/$@ -C build/ctemplates
build/ctemplates.html: \
	build/ctemplates/cgm.c.html \
	build/ctemplates/darray.h.html \
	build/ctemplates/example.c.html

# index
build/index.html: index.dnd
	dndc $< -o $@ -d Depends/$@

.PHONY: all
all: \
	docs/ctemplates.html \
	docs/index.html \


.PHONY: clean
clean:
	rm -rf Depends
	rm -rf build
	rm -rf docs

.DEFAULT_GOAL:=all
