build/fixing-c-biggest-mistake: ; mkdir -p $@

build/fixing-c-biggest-mistake/%.c.html: fixing-c-biggest-mistake/%.c | build/fixing-c-biggest-mistake
	python3 -m cdoc $< -o $@
build/fixing-c-biggest-mistake/%.h.html: fixing-c-biggest-mistake/%.h | build/fixing-c-biggest-mistake
	python3 -m cdoc $< -o $@
build/fixing-c-biggest-mistake.html: fixing-c-biggest-mistake/fixing-c-biggest-mistake.dnd | build Depends/build build/fixing-c-biggest-mistake
	dndc $< -o $@ -d Depends/$@.dep -C build/fixing-c-biggest-mistake

PAGES+=docs/fixing-c-biggest-mistake.html
