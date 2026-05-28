build/adding-reflection-to-C: ; mkdir -p $@

build/adding-reflection-to-C/%.c.html: adding-reflection-to-C/%.c | build/adding-reflection-to-C
	python3 -m cdoc $< -o $@
build/adding-reflection-to-C/%.h.html: adding-reflection-to-C/%.h | build/adding-reflection-to-C
	python3 -m cdoc $< -o $@
build/adding-reflection-to-C.html: adding-reflection-to-C/adding-reflection-to-C.dnd | build Depends/build build/adding-reflection-to-C
	dndc $< -o $@ -d Depends/$@.dep -C build/adding-reflection-to-C

build/adding-reflection-to-C.html: \
	build/adding-reflection-to-C/typeinfo.h.html \
	build/adding-reflection-to-C/option-1.c.html \
	build/adding-reflection-to-C/option-2.c.html \
	build/adding-reflection-to-C/option-4.c.html \
	build/adding-reflection-to-C/usage-1.c.html \
	build/adding-reflection-to-C/usage-2.c.html \

PAGES+=docs/adding-reflection-to-C.html

build/c-hash-table.html: \
	build/c-hash-table/ctable.c.html \
	build/c-hash-table/iter.c.html
