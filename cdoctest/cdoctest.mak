build/cdoctest: ; mkdir -p $@

build/cdoctest/%.c.html: cdoctest/%.c | build/cdoctest
	python3 -m cdoc $< -o $@
build/cdoctest/%.h.html: cdoctest/%.h | build/cdoctest
	python3 -m cdoc $< -o $@
build/cdoctest.html: cdoctest/cdoctest.dnd | build Depends/build build/cdoctest
	dndc $< -o $@ -d Depends/$@.dep -C build/cdoctest
build/cdoctest.html: \
	build/cdoctest/some_api.h.html \
	build/cdoctest/test_some_api_docs.c.html
build/cdoctest/some_api.h.html: cdoctest/some_api.h | build/cdoctest
	python3 -m cdoc $< -o $@ --cflags -include stdio.h -DSOME_API_EXAMPLE=1

PAGES+=docs/cdoctest.html
