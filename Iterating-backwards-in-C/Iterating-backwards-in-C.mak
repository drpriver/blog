build/Iterating-backwards-in-C: ; mkdir -p $@

build/Iterating-backwards-in-C/%.c.html: Iterating-backwards-in-C/%.c | build/Iterating-backwards-in-C
	python3 -m cdoc $< -o $@
build/Iterating-backwards-in-C/%.h.html: Iterating-backwards-in-C/%.h | build/Iterating-backwards-in-C
	python3 -m cdoc $< -o $@
build/Iterating-backwards-in-C/inline-c.html.json: Iterating-backwards-in-C/Iterating-backwards-in-C.dnd highlight-c.dnd highlight_c.py cdoc.py | build/Iterating-backwards-in-C
	dndc $< --dont-write --allow-js-write --jsargs '{"extract_c":true}' -C build/Iterating-backwards-in-C
	python3 highlight_c.py build/Iterating-backwards-in-C/inline-c.json $@

build/Iterating-backwards-in-C.html: Iterating-backwards-in-C/Iterating-backwards-in-C.dnd build/Iterating-backwards-in-C/inline-c.html.json highlight-c.dnd | build Depends/build build/Iterating-backwards-in-C
	dndc $< -o $@ -d Depends/$@.dep -C build/Iterating-backwards-in-C

PAGES+=docs/Iterating-backwards-in-C.html
