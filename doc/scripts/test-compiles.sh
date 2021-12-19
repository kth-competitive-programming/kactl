mkdir -p build
FILE="$1"
echo "
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
# Catching silly mistakes with GCC: https://codeforces.com/blog/entry/15547
g++  -Wall -Wextra -pedantic -Wconversion -Wno-unused-result -Wfatal-errors -DLOCAL -std=c++2a  -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector build/temp.cpp && rm a.out build/temp.cpp
