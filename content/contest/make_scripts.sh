echo 'g++ -Wall -O -o $1 $1.cpp' > c  # Compiles
echo './$1 < $1.in' > r               # Runs
echo 'a2ps --line-numbers=1 $1' > p   # Prints
echo 'cp template.cpp $1.cpp' > n     # Copies template

chmod +x c r p n
