set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cul
sy on   |   im jk <esc>   |   im kj <esc>   |   no ; :

com! -buffer -range=% Hash exe "<line1>,<line2>!cpp -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c1-6" |y|sil u|echom @"