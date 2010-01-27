# .bashrc configuration file
# Create file 'template.cpp' and folder 'backup'
n () { cp template.cpp "$*.cpp"; }
r () { eval "./$* < $*.in"; }
d () { eval "r $* | diff - $*.out"; }
c () { eval "cp $*.cpp ./backup/$*_`date +%H%M%S`.cpp; g++ -o $* $*.cpp -O2 -Wall"; }
p () { a2ps --line-numbers=1 "$*"; }

# Check that pahts and keycodes with xev!
# F10 = '<', F11 = '>', F12 = '|'
se () { xmodmap /usr/share/xmodmap/xmodmap.se -e "keycode 76 = less" -e "keycode 95 = greater" -e "keycode 96 = bar"; }
us () { xmodmap /usr/share/xmodmap/xmodmap.us; }

