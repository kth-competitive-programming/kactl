#!/usr/bin/env bash
DIR=${1:-.}
tests="$(find $DIR/stress-tests -name '*.cpp')"
declare -i pass=0
declare -i fail=0
failTests=""
ulimit -s 524288 # For 2-sat test
for test in $tests; do
    echo "$(basename $test): "
    start=`date +%s.%N`
    g++ -std=c++17 -O2 $test && ./a.out
    retCode=$?
    if (($retCode != 0)); then
        echo "Failed with $retCode"
        fail+=1
        failTests="$failTests$test\n"
    else
        pass+=1
    fi
    end=`date +%s.%N`
    runtime=$( echo "$end - $start" | bc -l )
    echo "Took $runtime seconds"
    rm -f a.out
    echo
done
echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failTests"
    exit 1
fi
