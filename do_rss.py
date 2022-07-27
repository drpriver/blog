from xml.etree.ElementTree import Element, SubElement, parse, register_namespace
import os
import re
import datetime

register_namespace('atom', "http://www.w3.org/2005/Atom")
def main() -> None:

    feed = parse('feed.xml')
    root = feed.getroot()
    channel = root[0]
    items = channel.findall('item')
    published_pages = set()
    for item in items:
        link = item.find('link')
        page = link.text.split('/')[-1]
        published_pages.add(page)
        item.find('author').text = 'david@davidpriver.com'
        with open('docs/'+page) as fp:
            item.find('description').text = fp.read()

    pages = [p for p in os.listdir('docs') if p != 'index.html' and p.endswith('.html') and p not in published_pages]

    for page in pages:
        with open('docs/'+page, 'r') as fp:
            text = fp.read()
        title = re.search('<title>(.*?)</title>', text)[1]
        item = SubElement(channel, 'item')
        titlenode = SubElement(item, 'title')
        titlenode.text=title
        description = SubElement(item, 'description')
        description.text = text
        pubdate = SubElement(item, 'pubDate')
        pubtext = datetime.datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S %z')
        if not pubtext.endswith('T'):
            pubtext += 'GMT'
        pubdate.text = pubtext
        link = SubElement(item, 'link')
        link.text = 'https://www.davidpriver.com/'+page
        author = SubElement(item, 'author')
        author.text = 'david@davidpriver.com'

    with open('feed.xml', 'wb') as fp:
        # fp.write(b'<?xml version="1.0" encoding="utf-8"?>\n')
        feed.write(fp, xml_declaration=True, encoding='utf-8')

if __name__ == '__main__':
    main()
