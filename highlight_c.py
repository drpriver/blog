"""Highlight the inline C exported by highlight-c.dnd between dndc passes."""
import argparse
import io
import json
from pathlib import Path
from tempfile import TemporaryDirectory

from cdoc import do_tags


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('output', type=Path)
    args = parser.parse_args()
    sources = json.loads(args.source.read_text())
    highlighted = []
    with TemporaryDirectory(dir=args.source.parent) as directory:
        snippet = Path(directory) / 'snippet.c'
        for source in sources:
            snippet.write_text(source)
            writer = do_tags(['-x', 'c'], str(snippet), 'clang', snippet=True)
            html = io.StringIO()
            writer.write(html)
            highlighted.append({'source': source, 'html': html.getvalue()})
    args.output.write_text(json.dumps(highlighted))


if __name__ == '__main__':
    main()
