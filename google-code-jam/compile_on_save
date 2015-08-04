#!/bin/bash
while true;
do 
    inotifywait -e modify *.cpp -qq
    TIME=`date`
    echo ===========================================
    echo $TIME
    time make clean test
    echo $TIME
    echo ===========================================
done
