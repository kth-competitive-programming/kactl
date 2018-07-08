#!/usr/bin/env python2
# encoding: utf-8

# Source code preprocessor for KACTL building process.
# Written by Håkan Terelius, 2008-11-24

from __future__ import print_function
import sys
import getopt


def escape(input):
    input = input.replace('<','\\ensuremath{<}')
    input = input.replace('>','\\ensuremath{>}')
    return input

def pathescape(input):
    input = input.replace('\\','\\\\')
    input = input.replace('_','\_')
    input = escape(input)
    return input

def codeescape(input):
    input = input.replace('_','\\_')
    input = input.replace('\n','\\\\\n')
    input = input.replace('{','\\{')
    input = input.replace('}','\\}')
    input = input.replace('^','\\ensuremath{\\hat{\\;}}')
    input = escape(input)
    return input

def ordoescape(input):
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
            return input[:start] + "\\bigo{" + input[start+2:end] + "}" + ordoescape(input[end+1:])
    return input

def addref(caption, outstream):
    caption = pathescape(caption).strip()
    print("\\kactlref{",caption,"}", file=outstream)
    with open('header.tmp', 'a') as f:
        f.write(caption + "\n")

def processwithcomments(caption, instream, outstream, listingslang = None):
    knowncommands = ['Author', 'Date', 'Description', 'Source', 'Time', 'Memory', 'License', 'Status', 'Usage']
    requiredcommands = ['Author', 'Description']
    includelist = []
    error = ""
    warning = ""
    # Read lines from source file
    try:
        lines = instream.readlines()
    except:
        error = "Could not read source."
    nlines = list()
    for line in lines:
        # Remove /// comments
        line = line.split("///")[0].rstrip()
        # Remove '#pragma once' and 'using namespace std;' lines
        if line == "#pragma once" or line == "using namespace std;":
            continue
        if line.endswith("/** exclude-line */"):
            continue
        # Check includes
        include = isinclude(line)
        if include is not None:
            includelist.append(include)
            continue
        nlines.append(line)
    # Remove and process /** */ comments
    source = '\n'.join(nlines)
    nsource = ''
    start = source.find("/**")
    end = 0
    commands = dict()
    while start >= 0 and not error:
        nsource = nsource.rstrip() + source[end:start]
        end = source.find("*/", start)
        if end<start:
            error = "Invalid /** */ comments."
            break
        comment = source[start+3:end].strip()
        end = end + 2
        start = source.find("/**",end)

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
            if allow_command and ind != -1 and ' ' not in cline[:ind]:
                if command:
                    if command not in knowncommands:
                        error = error + "Unknown command: " + command + ". "
                    commands[command] = value.lstrip()
                command = cline[:ind]
                value = cline[ind+1:].strip()
            else:
                value = value + '\n' + cline
        if command:
            if command not in knowncommands:
                error = error + "Unknown command: " + command + ". "
            commands[command] = value.lstrip()
    for rcommand in sorted(set(requiredcommands) - set(commands)):
        error = error + "Missing command: " + rcommand + ". "
    if end>=0:
        nsource = nsource.rstrip() + source[end:]
    nsource = nsource.strip()

    # Produce output
    if warning:
        print("\kactlwarning{",caption,":",warning,"}", file=outstream)
    if error:
        print("\kactlerror{",caption,":",error,"}", file=outstream)
    else:
        addref(caption, outstream)
        if "Description" in commands and len(commands["Description"])>0:
            print("\\defdescription{",escape(commands["Description"]),"}", file=outstream)
        if "Usage" in commands and len(commands["Usage"])>0:
            print("\\defusage{",codeescape(commands["Usage"]),"}", file=outstream)
        if "Time" in commands and len(commands["Time"])>0:
            print("\\deftime{",ordoescape(commands["Time"]),"}", file=outstream)
        if "Memory" in commands and len(commands["Memory"])>0:
            print("\\defmemory{",ordoescape(commands["Memory"]),"}", file=outstream)
        if includelist:
            print("\\leftcaption{",pathescape(", ".join(includelist)),"}", file=outstream)
        if nsource:
            print("\\rightcaption{",str(linecount(nsource))," lines}", file=outstream)
        print("\\begin{lstlisting}[caption={",pathescape(caption),"}", file=outstream)
        if listingslang is not None:
            print(", language="+listingslang, file=outstream)
        print("]", file=outstream)
        print(nsource, file=outstream)
        print("\\end{lstlisting}", file=outstream)

def processraw(caption, instream, outstream, listingslang = 'raw'):
    try:
        source = instream.read().strip()
        addref(caption, outstream)
        print("\\rightcaption{",str(linecount(source))," lines}", file=outstream)
        print("\\begin{lstlisting}[language="+listingslang+",caption={",pathescape(caption),"}]", file=outstream)
        print(source, file=outstream)
        print("\\end{lstlisting}", file=outstream)
    except:
        print("\kactlerror{Could not read source.}", file=outstream)

def linecount(source):
    return source.count("\n")+1

def isinclude(line):
    line = line.strip()
    if line.startswith("#include") and not line.endswith("/** keep-include */"):
        return line[8:].strip()
    return None

def getlang(input):
    return input.rsplit('.',1)[-1]

def getfilename(input):
    return input.rsplit('/',1)[-1]

def print_header(data, outstream):
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
    def adjust(name):
        return name if name.startswith('.') else name.split('.')[0]
    print('\\enspace{}'.join(map(adjust, lines[:ind])), file=outstream)
    with open('header.tmp', 'w') as f:
        for line in lines[ind:]:
            f.write(line + "\n")

def main():
    language = None
    caption = None
    instream = sys.stdin
    outstream = sys.stdout
    print_header_value = None
    try:
        opts, args = getopt.getopt(sys.argv[1:], "ho:i:l:c:", ["help", "output=", "input=", "language=", "caption=", "print-header="])
        for option, value in opts:
            if option in ("-h", "--help"):
                print("This is the help section for this program")
                print()
                print("Available commands are:")
                print("\t -o --output")
                print("\t -h --help")
                print("\t -i --input")
                print("\t -l --language")
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
        if print_header_value is not None:
            print_header(print_header_value, outstream)
            return
        print(" * \x1b[1m{}\x1b[0m".format(caption))
        if language == "cpp" or language == "cc" or language == "c" or language == "h" or language == "hpp":
            processwithcomments(caption, instream, outstream)
        elif language == "java":
            processwithcomments(caption, instream, outstream, 'Java')
        elif language == "ps":
            processraw(caption, instream, outstream) # PostScript was added in listings v1.4
        elif language == "raw":
            processraw(caption, instream, outstream)
        elif language == "rawcpp":
            processraw(caption, instream, outstream, 'C++')
        elif language == "sh":
            processraw(caption, instream, outstream, 'bash')
        else:
            raise ValueError("Unkown language: " + str(language))
    except (ValueError, getopt.GetoptError, IOError) as err:
        print(str(err), file=sys.stderr)
        print("\t for help use --help", file=sys.stderr)
        return 2

if __name__ == "__main__":
    exit(main())
