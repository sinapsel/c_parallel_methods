#!/bin/bash

for var in {100000..20000000..10000}
do
# echo $var
    (echo 4 $var 10 20 | wine ./lab2_win.exe) >> proc4_win.csv
done