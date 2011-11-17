# .bashrc configuration file
r () { eval "./$* < $*.in"; }         #run
d () { eval "r $* | diff - $*.out"; } #diff
p () { a2ps --line-numbers=1 "$*"; }  #print
c () { eval "~/script/c $*"; }        #compile
#We have to create a script for compiling, because otherwise
#compiling in vim with ":make" wouldn't work.

# Only used for strange keyboads. Check that paths and
# keycodes with xev!
# F10 = '<', F11 = '>', F12 = '|'
se () { xmodmap /usr/share/xmodmap/xmodmap.se -e "keycode 76 = less" -e "keycode 95 = greater" -e "keycode 96 = bar"; }
us () { xmodmap /usr/share/xmodmap/xmodmap.us; }
