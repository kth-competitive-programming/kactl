mkdir backup
mkdir script
cd script
echo 'cp $1.cpp ./backup/$1_`date +%H%M%S`.cpp; g++ -Wall -O -o $1 $1.cpp' > c # Backup and compile
echo './$1 < $1.in' > r               # Runs
echo 'r $1 | diff - $1.out' > d       # Diff
echo 'a2ps --line-numbers=1 $1' > p   # Prints

chmod +x c r d p
