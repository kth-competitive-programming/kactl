#!/usr/bin/env bash
DIR=${1:-.}
tests="$(find $DIR -name '*.cpp')"
declare -i pass=0
declare -i fail=0
failTests=""
echo -e $failTests
for test in $tests; do
    echo "$(basename $test): "
    g++ -std=c++14 -O2 $test && ./a.out
    retCode=$?
    if (($retCode != 0)); then
        echo $retCode
        fail+=1
        failTests="$failTests$test\n"
    else
        pass+=1
    fi
    rm -f a.out
    echo
done
echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
    echo "No tests failed"
else
    echo -e "These tests failed: \n $failTests"
fi
