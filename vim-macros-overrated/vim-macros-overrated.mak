build/vim-macros-overrated.html: vim-macros-overrated/vim-macros-overrated.dnd | build Depends/build
	dndc $< -o $@ -d Depends/$@.dep

build/vim-macros-overrated.html: vim-macros-overrated/highlight-python.dnd

PAGES+=docs/vim-macros-overrated.html
