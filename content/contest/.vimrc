set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cul
sy on   |   im jk <esc>   |   im kj <esc>   |   no ; :
" Select region and then type :H to hash your selection.
" Useful for verifying that there aren't mistypes
cmap H w !cpp -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c1-6
