build/undefined-behavior.html: undefined-behavior/undefined-behavior.dnd | build Depends/build
	dndc $< -o $@ -d Depends/$@.dep

PAGES+=docs/undefined-behavior.html
