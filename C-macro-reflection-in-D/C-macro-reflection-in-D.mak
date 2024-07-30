build/C-macro-reflection-in-D: ; mkdir -p $@

build/C-macro-reflection-in-D/%.c.html: C-macro-reflection-in-D/%.c | build/C-macro-reflection-in-D
	python3 -m cdoc $< -o $@
build/C-macro-reflection-in-D/%.d.html: C-macro-reflection-in-D/%.d | build/C-macro-reflection-in-D
	python3 -m cdoc $< -o $@
build/C-macro-reflection-in-D/%.h.html: C-macro-reflection-in-D/%.h | build/C-macro-reflection-in-D
	python3 -m cdoc $< -o $@
build/C-macro-reflection-in-D.html: C-macro-reflection-in-D/C-macro-reflection-in-D.dnd | build Depends/build build/C-macro-reflection-in-D
	dndc $< -o $@ -d Depends/$@.dep -C build/C-macro-reflection-in-D

PAGES+=docs/C-macro-reflection-in-D.html
