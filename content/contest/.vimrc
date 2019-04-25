set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cul
sy on   |   im jk <esc>   |   im kj <esc>   |   no ; :

com -range=% -nargs=1 P exe "<line1>,<line2>!".<q-args> |y|sil u|echom @"
au FileType cpp com! -buffer -range=% Hash <line1>,<line2>P cpp -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c1-5
