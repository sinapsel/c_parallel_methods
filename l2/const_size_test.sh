#!/bin/bash

for var in {1..32}
do
# echo $var
    (echo $var 1000000 10 20 | ./lab2) >> size_1M.csv
    (echo $var 1000000 10 20 | ./lab2) >> size_1M.csv
    (echo $var 1000000 10 20 | ./lab2) >> size_1M.csv
done