mkdir -p build
FILE="$1"
echo "
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
# Catching silly mistakes with GCC: https://codeforces.com/blog/entry/15547
g++ -Wall -Wextra -O2 -Wfatal-errors -Wconversion -std=c++14 -pedantic -Wno-unused-result -Wshadow -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align build/temp.cpp && rm a.out build/temp.cpp
