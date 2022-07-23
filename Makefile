Depends: ; mkdir -p $@
Depends/build: ; mkdir -p $@
blog: ; mkdir -p $@
build: ; mkdir -p $@
include $(wildcard Depends/*.dep)
include $(wildcard Depends/build/*.dep)

blog/%.html: build/%.html | build blog
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

.PHONY: all
all: \
	blog/ctemplates.html \


.PHONY: clean
clean:
	rm -rf Depends
	rm -rf build
	rm -rf blog

.DEFAULT_GOAL:=all
