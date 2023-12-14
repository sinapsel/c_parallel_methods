#!/bin/bash

for var in {1000..1000000..1000}
do
# echo $var
    (echo 8 $var 10 20 | ./lab2) >> proc8_k.csv
done