build/creification: ; mkdir -p $@

build/creification/%.c.html: creification/%.c | build/creification
	python3 -m cdoc $< -o $@
build/creification/%.h.html: creification/%.h | build/creification
	python3 -m cdoc $< -o $@
build/creification.html: creification/creification.dnd | build Depends/build build/creification
	dndc $< -o $@ -d Depends/$@.dep -C build/creification
build/creification.html: \
	build/creification/anypointer.h.html \
	build/creification/intro.c.html \
	build/creification/problem.c.html \
	build/creification/generic.c.html \
	build/creification/generictag.c.html \
	build/creification/genericliteral.c.html

build/creification/intro.c.html: creification/anypointer.h
build/creification/problem.c.html: creification/anypointer.h
build/creification/generic.c.html: creification/anypointer.h
build/creification/generictag.c.html: creification/anypointer.h
build/creification/genericliteral.c.html:  creification/anypointer.h

PAGES+=docs/creification.html
