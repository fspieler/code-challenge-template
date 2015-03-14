#!/bin/bash

DELETE_NUM=$1
TEST_NUM=$(expr $(cat test/test_number) - 1)
echo $DELETE_NUM
echo $TEST_NUM

for i in `seq $DELETE_NUM $TEST_NUM`;
do
    echo $i
    echo test/inputs/`expr $i + 1`
    mv test/inputs/`expr $i + 1` test/inputs/$i
    mv test/expected_outputs/`expr $i + 1` test/expected_outputs/$i
done

echo $TEST_NUM > test/test_number
