#!/usr/bin/env python3
# encoding: utf-8

import json
import re
import os

# Creates VSCode JSON snippets out of kactl code
# running this file directly combines all of the snippets into one
# build() is called from the preprocessor to build the individual file snippets

prefix = 'kactl_'
langs = {
    'C++': 'cpp',
    'Java': 'java',
    'Python': 'python'
}
tab_pattern = re.compile(r'^(\t*) {2}')
line_pattern = re.compile(r'\r?\n')

# convert a line that starts with tabs into one that starts with spaces
def spaces_to_tabs(str: str) -> str:
    while tab_pattern.match(str):
        str = tab_pattern.sub(r'\1\t', str)
    return str

def remove_extension(filename: str) -> str:
    return filename.rsplit('.', 1)[0]

# create a snippet for a single file, and put it in snippets/lang/name.json
# called from the preprocessor
def build(filename: str, commands: dict[str, str], nsource: str, comment : str, lang: str):

    # do not make the snippet if it's not code
    if lang not in langs:
        return

    if lang == 'C++':
        nsource = f"/*{comment}\n */\n{nsource}"

    name = remove_extension(filename)

    # build json object
    obj = {}
    obj['prefix'] = [prefix + name]
    obj['body'] = [spaces_to_tabs(line) for line in line_pattern.split(nsource)]
    if 'Description' in commands:
        obj['description'] = commands['Description']

    path = f'snippets/{langs[lang]}/'

    if not os.path.exists(path):
        os.makedirs(path)

    # dump json object into file
    with open(f'{path}{name}.json', 'w') as f:
        json.dump({filename: obj}, f, indent='\t', sort_keys=True)

# reads all of the snippets in a lang's snippet folder, and combines them into one
# works with C++, should work with Java and Python as well (in theory)
def combine():
    for key in langs:
        lang = langs[key]
        lang_obj = {}
        lang_path = f'snippets/{lang}/'

        # don't make empty files
        if not os.path.isdir(lang_path):
            continue

        # dump each json object into the lang's master object
        for filename in os.listdir(lang_path):
            with open(lang_path + filename, 'r') as f:
                lang_obj.update(json.load(f))

        # dump nonempty json object into file
        if len(lang_obj) > 0:
            with open(f'snippets/{lang}.json', 'w') as f:
                json.dump(lang_obj, f, indent='\t', sort_keys=True)

def main():
    combine()

if __name__ == "__main__":
    main()
