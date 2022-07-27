build/runvarsargs.html: runvarsargs/runvarsargs.dnd | build Depends/build
	dndc $< -o $@ -d Depends/$@.dep

build/runvarsargs.html: runvarsargs/highlight-python.dnd

PAGES+=docs/runvarsargs.html
