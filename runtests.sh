tests="$(find fuzz-tests -name '*.cpp')"
for test in $tests; do
    basename $test
    g++ -std=c++14 $test
    ./a.out
    echo $?
    rm a.out
done
