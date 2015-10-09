FILE="$1"
echo "
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ -Wall -Wextra -Wfatal-errors -Wconversion -std=c++11 build/temp.cpp && rm a.out build/temp.cpp
