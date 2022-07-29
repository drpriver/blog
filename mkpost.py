#!/usr/bin/env python3
import argparse
import os
import shutil
from enum import Enum
import datetime

class Langs(str, Enum):
    C = 'C'
    Python = 'python'
    Plain = 'plain'
    def __str__(self) -> str:
        return self.value

def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('name', nargs='+')
    parser.add_argument('-l', '--lang', required=True, choices={'c', 'C', 'py', 'python', 'plain'})

    args = parser.parse_args()
    args.lang = {
        'c':'C',
        'py':'python',
    }.get(args.lang, args.lang)
    args.lang = Langs(args.lang)
    args.name = ' '.join(args.name)

    run(**vars(args))

def run(name:str, lang:Langs) -> None:
    name = name.replace(' ', '-')
    os.makedirs(name)
    match lang:
        case Langs.C:
            ctemplate(name)
        case Langs.Python:
            pytemplate(name)
        case Langs.Plain:
            plaintemplate(name)
    with open('Makefile', 'a') as fp:
        print(f'\ninclude {name}/{name}.mak', file=fp)
    try:
        with open('.vimrc', 'r') as fp:
            vimrc = fp.read().strip()
    except IOError:
        vimrc = 'setpath=.,'
    with open('.vimrc', 'w') as fp:
        print(vimrc+','+name, file=fp)


def ctemplate(name:str) -> None:
    mkfile = f'''build/{name}: ; mkdir -p $@

build/{name}/%.c.html: {name}/%.c | build/{name}
\tpython3 -m cdoc $< -o $@
build/{name}/%.h.html: {name}/%.h | build/{name}
\tpython3 -m cdoc $< -o $@
build/{name}.html: {name}/{name}.dnd | build Depends/build build/{name}
\tdndc $< -o $@ -d Depends/$@.dep -C build/{name}

PAGES+=docs/{name}.html
'''
    with open(f'{name}/{name}.mak', 'w') as fp:
        fp.write(mkfile)
    with open(f'{name}/{name}.dnd', 'w') as fp:
        def p(arg):
            print(arg, file=fp)
        p('::css #import')
        p('  ../../c.css')
        p('::js')
        p("  let wrapped = ctx.select_nodes({attributes:['wrapped']});")
        p('  for(let w of wrapped){')
        p("    w.insert_child(0, '<pre>');")
        p("    w.add_child('</pre>');")
        p('  }')
        p('  //endjs')
        p(name+'::title')
        today = datetime.date.today()
        p(today.strftime('<i>[David Priver], %B %dth, %Y</i>'))
        p('')
        p('::raw')
        p('  <article>')
        p('')
        p('')
        p('::raw')
        p('  </article>')
        p('Copyright::md')
        p('  All code in this article is released into the public domain.')
        p('')
        p('::links')
        p('  home = https://www.davidpriver.com')
        p('  David Priver = mailto:david@davidpriver.com')

def pytemplate(name:str) -> None:
    mkfile=f'''build/{name}.html: {name}/{name}.dnd | build Depends/build
\tdndc $< -o $@ -d Depends/$@.dep

build/{name}.html: {name}/highlight-python.dnd

PAGES+=docs/{name}.html
'''
    with open(f'{name}/{name}.mak', 'w') as fp:
        fp.write(mkfile)
    with open(f'{name}/{name}.dnd', 'w') as fp:
        pass
    shutil.copy('highlight-python.dnd', name)

def plaintemplate(name:str) -> None:
    mkfile=f'''build/{name}.html: {name}/{name}.dnd | build Depends/build
\tdndc $< -o $@ -d Depends/$@.dep

PAGES+=docs/{name}.html
'''
    with open(f'{name}/{name}.mak', 'w') as fp:
        fp.write(mkfile)
    with open(f'{name}/{name}.dnd', 'w') as fp:
        pass


if __name__ == '__main__':
    main()
