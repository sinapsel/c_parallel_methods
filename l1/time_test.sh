#!/bin/bash

for var in {8..32768..8}
do
# echo $var
    (echo $var 20 | ./lab1 -t) >> times.csv
done