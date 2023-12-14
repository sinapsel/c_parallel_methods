set term png
set output "plot21.png"


f1(x) = a1 * x + b1
f2(x) = a2 * x + b2
f3(x) = a3 * x + b3
fit f1(x) 'times.csv' using 1:2 via a1,b1
fit f2(x) 'times.csv' using 1:3 via a2,b2
fit f3(x) 'times.csv' using 1:4 via a3,b3

plot 'times.csv' using 1:2 title 'linear',\
    '' using 1:3 title 'SMID',\
    '' using 1:4 title 'VEC',\
    f1(x) lw 3 title 'linear fit',\
    f2(x) lw 3 title 'smid fit',\
    f3(x) lw 3 title 'vec fit'