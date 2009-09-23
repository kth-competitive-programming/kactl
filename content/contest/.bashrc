# .bashrc configuration file
# Create file 'template.cpp' and folder 'backup'
n () { cp template.cpp "$*.cpp"; }
r () { eval "./$* < $*.in"; }
c () { eval "cp $*.cpp ./backup/$*_`date +%H%M%S`.cpp; g++ -o $* $*.cpp -O2 -Wall"; }
p () { a2ps --line-numbers=1 "$*"; }
