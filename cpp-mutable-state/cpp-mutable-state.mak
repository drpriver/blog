build/cpp-mutable-state: ; mkdir -p $@

build/cpp-mutable-state/%.c.html: cpp-mutable-state/%.c | build/cpp-mutable-state
	python3 -m cdoc $< -o $@
build/cpp-mutable-state/%.h.html: cpp-mutable-state/%.h | build/cpp-mutable-state
	python3 -m cdoc $< -o $@
build/cpp-mutable-state/inline-c.html.json: cpp-mutable-state/cpp-mutable-state.dnd highlight-c.dnd highlight_c.py cdoc.py | build/cpp-mutable-state
	dndc $< --dont-write --allow-js-write --jsargs '{"extract_c":true}' -C build/cpp-mutable-state
	python3 highlight_c.py build/cpp-mutable-state/inline-c.json $@

build/cpp-mutable-state.html: cpp-mutable-state/cpp-mutable-state.dnd build/cpp-mutable-state/inline-c.html.json highlight-c.dnd | build Depends/build build/cpp-mutable-state
	dndc $< -o $@ -d Depends/$@.dep -C build/cpp-mutable-state

PAGES+=docs/cpp-mutable-state.html
