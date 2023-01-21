build/c-in-wasm: ; mkdir -p $@

build/c-in-wasm/%.c.html: c-in-wasm/%.c | build/c-in-wasm
	python3 -m cdoc $< -o $@
build/c-in-wasm/%.h.html: c-in-wasm/%.h | build/c-in-wasm
	python3 -m cdoc $< -o $@
build/c-in-wasm.html: c-in-wasm/c-in-wasm.dnd | build Depends/build build/c-in-wasm
	dndc $< -o $@ -d Depends/$@.dep -C build/c-in-wasm

build/c-in-wasm.html: \
	build/c-in-wasm/primitive_malloc.c.html \
	build/c-in-wasm/jsinter.c.html \
	build/c-in-wasm/example.wasm \
	build/c-in-wasm/example.c.html
build/c-in-wasm/jsinter.c.html: c-in-wasm/jsinter.c | build/c-in-wasm
	python3 -m cdoc $< -o $@ --cflags -include c-in-wasm/primitive_malloc.c
build/c-in-wasm/example.wasm: c-in-wasm/example.c
	$(WCC) $< -o $@ \
    --target=wasm32 --no-standard-libraries \
    -Wl,--export-all -Wl,--no-entry \
    -Wl,--allow-undefined -ffreestanding \
    -nostdinc \
    -mbulk-memory -mreference-types \
    -mmultivalue -mmutable-globals \
    -mnontrapping-fptoint -msign-ext \
    -O3 -g

PAGES+=docs/c-in-wasm.html
