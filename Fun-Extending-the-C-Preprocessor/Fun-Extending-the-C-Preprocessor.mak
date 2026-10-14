build/Fun-Extending-the-C-Preprocessor: ; mkdir -p $@

build/Fun-Extending-the-C-Preprocessor/%.c.html: Fun-Extending-the-C-Preprocessor/%.c | build/Fun-Extending-the-C-Preprocessor
	python3 -m cdoc $< -o $@
build/Fun-Extending-the-C-Preprocessor/%.h.html: Fun-Extending-the-C-Preprocessor/%.h | build/Fun-Extending-the-C-Preprocessor
	python3 -m cdoc $< -o $@
build/Fun-Extending-the-C-Preprocessor.html: Fun-Extending-the-C-Preprocessor/Fun-Extending-the-C-Preprocessor.dnd | build Depends/build build/Fun-Extending-the-C-Preprocessor
	dndc $< -o $@ -d Depends/$@.dep -C build/Fun-Extending-the-C-Preprocessor

PAGES+=docs/Fun-Extending-the-C-Preprocessor.html
