# .bashrc configuration file
# Create file 'template.cpp' and folder 'backup'
r () { eval "./$* < $*.in"; } #run
d () { eval "r $* | diff - $*.out"; } #diff
c () { eval "cp $*.cpp ./backup/$*_`date +%H%M%S`.cpp; g++ -o $* $*.cpp -O2 -Wall"; }
p () { a2ps --line-numbers=1 "$*"; } #print

# Only used for strange keyboads. Check that pahts and keycodes with xev!
# F10 = '<', F11 = '>', F12 = '|'
se () { xmodmap /usr/share/xmodmap/xmodmap.se -e "keycode 76 = less" -e "keycode 95 = greater" -e "keycode 96 = bar"; }
us () { xmodmap /usr/share/xmodmap/xmodmap.us; }
