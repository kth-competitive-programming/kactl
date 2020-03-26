#!/usr/bin/env bash
DIR=${1:-.}
SCRIPT_DIR=$DIR/doc/scripts
tests="$(find $DIR/content -name '*.h' | grep -vFf $SCRIPT_DIR/skip_headers)"
echo "skipped: "
find $DIR/content -name '*.h' | grep -Ff $SCRIPT_DIR/skip_headers
declare -i pass=0
declare -i fail=0
failHeaders=""
ulimit -s 524288 # For 2-sat test
for test in $tests; do
    echo "$(basename $test): "
    $SCRIPT_DIR/test-compiles.sh $test
    retCode=$?
    if (($retCode != 0)); then
        echo $retCode
        fail+=1
        failHeaders="$failHeaders$test\n"
    else
        pass+=1
    fi
    rm -f a.out
    echo
done
echo "$pass/$(($pass+$fail)) tests passed"

if (($pass == 0)); then
    echo "No tests found (make sure skip_headers doesn't have whitespace lines)"
    exit 1
elif (($fail == 0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failHeaders"
    exit 1
fi
