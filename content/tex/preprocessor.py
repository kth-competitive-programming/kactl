#!/usr/bin/env python3
# encoding: utf-8

# Source code preprocessor for KACTL build process.
# License: CC0

import sys
import getopt
import subprocess
import snippets

instream = sys.stdin
outstream = sys.stdout

def escape(input: str) -> str:
    input = input.replace('<', r'\ensuremath{<}')
    input = input.replace('>', r'\ensuremath{>}')
    return input

def pathescape(input: str) -> str:
    input = input.replace('\\', r'\\')
    input = input.replace('_', r'\_')
    input = escape(input)
    return input

def codeescape(input: str) -> str:
    input = input.replace('_', r'\_')
    input = input.replace('\n', '\\\\\n')
    input = input.replace('{', r'\{')
    input = input.replace('}', r'\}')
    input = input.replace('^', r'\ensuremath{\hat{\;}}')
    input = escape(input)
    return input

def ordoescape(input: str, esc: bool = True) -> str:
    if esc:
        input = escape(input)
    start = input.find("O(")
    if start >= 0:
        bracketcount = 1
        end = start+1
        while end+1<len(input) and bracketcount>0:
            end = end + 1
            if input[end] == '(':
                bracketcount = bracketcount + 1
            elif input[end] == ')':
                bracketcount = bracketcount - 1
        if bracketcount == 0:
            return rf"{input[:start]}\bigo{{{input[start+2:end]}}}{ordoescape(input[end+1:], False)}"
    return input

def addref(caption: str):
    caption = pathescape(caption).strip()
    print(rf"\kactlref{{{caption}}}", file=outstream)
    with open('header.tmp', 'a') as f:
        f.write(f"{caption}\n")

COMMENT_TYPES = [
    ('/**', '*/'),
    ("'''", "'''"),
    ('"""', '"""'),
]

def find_start_comment(source: str, start: int | None = None) -> tuple[int, int, str]:
    first = (-1, -1, "")
    for s, e in COMMENT_TYPES:
        i = source.find(s, start)
        if i != -1 and (i < first[0] or first[0] == -1):
            first = (i, i + len(s), e)

    return first

def processwithcomments(caption: str, listingslang: str, make_snippets: bool = False):
    knowncommands = ['Author', 'Date', 'Description', 'Source', 'Time', 'Memory', 'License', 'Status', 'Usage', 'Details']
    requiredcommands = ['Author', 'Description']
    if listingslang not in ['C++', 'Java']:
        requiredcommands = []
    includelist: list[str] = []
    error = ""
    warning = ""
    # Read lines from source file
    try:
        lines = instream.readlines()
    except:
        error = "Could not read source."
        lines = []
    nlines: list[str] = []
    for line in lines:
        if 'exclude-line' in line:
            continue
        if 'include-line' in line:
            line = line.replace('// ', '', 1)
        had_comment = "///" in line
        keep_include = 'keep-include' in line
        # Remove /// comments
        line = line.split("///")[0].rstrip()
        # Remove '#pragma once' lines
        if line == "#pragma once":
            continue
        if had_comment and not line:
            continue
        # Check includes
        include = parse_include(line)
        if include is not None and not keep_include:
            includelist.append(include)
            continue
        nlines.append(line)
    # Remove and process multiline comments
    source = '\n'.join(nlines)
    nsource = ''
    start, start2, end_str = find_start_comment(source)
    end = 0
    commands: dict[str, str] = {}
    while start >= 0 and not error:
        nsource = nsource.rstrip() + source[end:start]
        end = source.find(end_str, start2)
        if end<start:
            error = f"Invalid {source[start:start2]} {end_str} comments."
            break
        comment = source[start2:end].strip()
        end += len(end_str)
        start, start2, end_str = find_start_comment(source, end)

        commentlines = comment.split('\n')
        command = None
        value = ""
        for cline in commentlines:
            allow_command = False
            cline = cline.strip()
            if cline.startswith('*'):
                cline = cline[1:].strip()
                allow_command = True
            ind = cline.find(':')
            if allow_command and ind != -1 and ' ' not in cline[:ind] and cline[0].isalpha() and cline[0].isupper():
                if command:
                    if command not in knowncommands:
                        error = f"{error}Unknown command: {command}. "
                    commands[command] = value.lstrip()
                command = cline[:ind]
                value = cline[ind+1:].strip()
            else:
                value = f"{value}\n{cline}"
        if command:
            if command not in knowncommands:
                error = f"{error}Unknown command: {command}. "
            commands[command] = value.lstrip()
    for rcommand in sorted(set(requiredcommands) - set(commands)):
        error = f"{error}Missing command: {rcommand}. "
    if end>=0:
        nsource = nsource.rstrip() + source[end:]
    nsource = nsource.strip()

    # create snippet
    if make_snippets:
        snippets.build(caption, commands, nsource, comment, listingslang)
        return

    if listingslang in ['C++', 'Java']:
        hash_script = 'hash'
        p = subprocess.Popen(['sh', f'content/contest/{hash_script}.sh'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, encoding="utf-8")
        hsh, _ = p.communicate(nsource)
        hsh = hsh.split(None, 1)[0]
        hsh = f"{hsh}, "
    else:
        hsh = ''
    # Produce output
    out: list[str] = []
    if warning:
        out.append(rf"\kactlwarning{{{caption}: {warning}}}")
    if error:
        out.append(rf"\kactlerror{{{caption}: {error}}}")
    else:
        addref(caption)
        if commands.get("Description"):
            out.append(rf"\defdescription{{{escape(commands['Description'])}}}")
        if commands.get("Usage"):
            out.append(rf"\defusage{{{codeescape(commands['Usage'])}}}")
        if commands.get("Time"):
            out.append(rf"\deftime{{{ordoescape(commands['Time'])}}}")
        if commands.get("Memory"):
            out.append(rf"\defmemory{{{ordoescape(commands['Memory'])}}}")
        if includelist:
            out.append(rf"\leftcaption{{{pathescape(', '.join(includelist))}}}")
        if nsource:
            out.append(rf"\rightcaption{{{hsh}{len(nsource.splitlines())} lines}}")
        langstr = f", language={listingslang}"
        out.append(rf"\begin{{lstlisting}}[caption={{{pathescape(caption)}}}{langstr}]")
        out.append(nsource)
        out.append(r"\end{lstlisting}")

    for line in out:
        print(line, file=outstream)

def processraw(caption: str, listingslang: str = 'raw'):
    try:
        source = instream.read().strip()
        addref(caption)
        print(rf"\rightcaption{{{len(source.splitlines())} lines}}", file=outstream)
        print(rf"\begin{{lstlisting}}[language={listingslang},caption={{{pathescape(caption)}}}]", file=outstream)
        print(source, file=outstream)
        print(r"\end{lstlisting}", file=outstream)
    except:
        print(r"\kactlerror{Could not read source.}", file=outstream)

def parse_include(line: str) -> str | None:
    line = line.strip()
    if line.startswith("#include"):
        return line[8:].strip()
    return None

def getlang(input: str) -> str:
    return input.rsplit('.',1)[-1]

def getfilename(input: str) -> str:
    return input.rsplit('/',1)[-1]

def print_header(data: str):
    parts = data.split('|')
    until = parts[0].strip() or parts[1].strip()
    if not until:
        # Nothing on this page, skip it.
        return
    with open('header.tmp') as f:
        lines = [x.strip() for x in f.readlines()]
    if until not in lines:
        # Nothing new on the page.
        return

    ind = lines.index(until) + 1
    header_length = len("".join(lines[:ind]))
    def adjust(name: str) -> str:
        return name if name.startswith('.') else name.split('.')[0]
    output = r"\enspace{}".join(map(adjust, lines[:ind]))
    font_size = 10
    if header_length > 150:
        font_size = 8
    output = rf"\hspace{{3mm}}\textbf{{{output}}}"
    output = f"\\fontsize{{{font_size}}}{{{font_size}}}{output}"
    print(output, file=outstream)
    with open('header.tmp', 'w') as f:
        for line in lines[ind:]:
            f.write(f"{line}\n")

def main():
    language = None
    caption = None
    global instream, outstream
    print_header_value = None
    make_snippets = False
    try:
        opts, _ = getopt.getopt(sys.argv[1:], "ho:i:l:c:s", ["help", "output=", "input=", "language=", "caption=", "print-header=", "snippet"])
        for option, value in opts:
            if option in ("-h", "--help"):
                print("This is the help section for this program")
                print()
                print("Available commands are:")
                print("\t -o --output")
                print("\t -h --help")
                print("\t -i --input")
                print("\t -l --language")
                print("\t -s --snippet")
                print("\t --print-header")
                return
            if option in ("-o", "--output"):
                outstream = open(value, "w")
            if option in ("-i", "--input"):
                instream = open(value)
                if language == None:
                    language = getlang(value)
                if caption == None:
                    caption = getfilename(value)
            if option in ("-l", "--language"):
                language = value
            if option in ("-c", "--caption"):
                caption = value
            if option == "--print-header":
                print_header_value = value
            if option in ("-s", "--snippet"):
                make_snippets = True
        if print_header_value is not None:
            print_header(print_header_value)
            return
        if language is None:
            raise ValueError("No language given")
        if caption is None:
            raise ValueError("No caption given")
        print(f" * \x1b[1m{caption}\x1b[0m")
        if language in ["cpp", "cc", "c", "h", "hpp"]:
            processwithcomments(caption, 'C++', make_snippets)
        elif language in ["java", "kt"]:
            processwithcomments(caption, 'Java', make_snippets)
        elif language == "py":
            processwithcomments(caption, 'Python', make_snippets)
        elif language in ["ps", "raw"]:
            processraw(caption) # PostScript was added in listings v1.4
        elif language == "rawcpp":
            processraw(caption, 'C++')
        elif language == "sh":
            processraw(caption, 'bash')
        elif language == "rawpy":
            processraw(caption, 'Python')
        else:
            raise ValueError(f"Unknown language: {language}")
    except (ValueError, getopt.GetoptError, IOError) as err:
        print(str(err), file=sys.stderr)
        print("\t for help use --help", file=sys.stderr)
        return 2

if __name__ == "__main__":
    exit(main())
