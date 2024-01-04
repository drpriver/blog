build/c-hash-table: ; mkdir -p $@

build/c-hash-table/ctable.c.html: c-hash-table/ctable.c | build/c-hash-table
	python3 -m cdoc $< -o $@ --cflags --include c-hash-table/decls.h
build/c-hash-table/iter.c.html: c-hash-table/iter.c | build/c-hash-table
	python3 -m cdoc $< -o $@ --cflags --include c-hash-table/decls2.h
build/c-hash-table/%.h.html: c-hash-table/%.h | build/c-hash-table
	python3 -m cdoc $< -o $@
build/c-hash-table.html: c-hash-table/c-hash-table.dnd | build Depends/build build/c-hash-table
	dndc $< -o $@ -d Depends/$@.dep -C build/c-hash-table

build/c-hash-table.html: \
	build/c-hash-table/ctable.c.html \
	build/c-hash-table/iter.c.html
PAGES+=docs/c-hash-table.html
