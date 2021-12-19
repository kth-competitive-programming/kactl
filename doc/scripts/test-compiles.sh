mkdir -p build
FILE="$1"
echo "
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
# Catching silly mistakes with GCC: https://codeforces.com/blog/entry/15547
g++  -Wall -Wextra -pedantic -Wconversion -Wno-unused-result -Wfatal-errors -std=c++14  -Wshadow -Wformat=2 -Wfloat-equal -Wcast-qual -Wcast-align build/temp.cpp && rm a.out build/temp.cpp
