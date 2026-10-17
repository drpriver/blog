build/Understanding-VLAs-in-C: ; mkdir -p $@

build/Understanding-VLAs-in-C/inline-c.html.json: Understanding-VLAs-in-C/Understanding-VLAs-in-C.dnd highlight-c.dnd highlight_c.py cdoc.py | build/Understanding-VLAs-in-C
	dndc $< --dont-write --allow-js-write --jsargs '{"extract_c":true}' -C build/Understanding-VLAs-in-C
	python3 highlight_c.py build/Understanding-VLAs-in-C/inline-c.json $@

build/Understanding-VLAs-in-C.html: Understanding-VLAs-in-C/Understanding-VLAs-in-C.dnd build/Understanding-VLAs-in-C/inline-c.html.json highlight-c.dnd | build Depends/build build/Understanding-VLAs-in-C
	dndc $< -o $@ -d Depends/$@.dep -C build/Understanding-VLAs-in-C

PAGES+=docs/Understanding-VLAs-in-C.html
