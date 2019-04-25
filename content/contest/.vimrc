set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cul
sy on   |   im jk <esc>   |   im kj <esc>   |   no ; :

com! -range=% Hash <line1>,<line2>w !cpp -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c1-6
