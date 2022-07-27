build/ctemplates: ; mkdir -p $@

build/ctemplates/%.c.html: ctemplates/%.c | build/ctemplates
	python3 -m cdoc $< -o $@
build/ctemplates/%.h.html: ctemplates/%.h | build/ctemplates
	python3 -m cdoc $< -o $@
build/ctemplates/darray.h.html: ctemplates/darray.h | build/ctemplates
	python3 -m cdoc $< -o $@ --cflags -DDARRAY_T=int
build/ctemplates.html: ctemplates/ctemplates.dnd | build Depends/build build/ctemplates
	dndc $< -o $@ -d Depends/$@.dep -C build/ctemplates
build/ctemplates.html: \
	build/ctemplates/cgm.c.html \
	build/ctemplates/darray.h.html \
	build/ctemplates/example.c.html

PAGES+=docs/ctemplates.html
