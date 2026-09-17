build/From-Tree-Walker-to-Bytecode: ; mkdir -p $@

build/From-Tree-Walker-to-Bytecode/%.c.html: From-Tree-Walker-to-Bytecode/%.c | build/From-Tree-Walker-to-Bytecode
	python3 -m cdoc $< -o $@
build/From-Tree-Walker-to-Bytecode/%.h.html: From-Tree-Walker-to-Bytecode/%.h | build/From-Tree-Walker-to-Bytecode
	python3 -m cdoc $< -o $@
build/From-Tree-Walker-to-Bytecode.html: From-Tree-Walker-to-Bytecode/From-Tree-Walker-to-Bytecode.dnd | build Depends/build build/From-Tree-Walker-to-Bytecode
	dndc $< -o $@ -d Depends/$@.dep -C build/From-Tree-Walker-to-Bytecode

PAGES+=docs/From-Tree-Walker-to-Bytecode.html
