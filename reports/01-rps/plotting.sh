#! /usr/bin/gnuplot -persist

set terminal dumb
set palette gray 

plot "./reports/01-rps/robyn-01.csv" using 9 w l
plot "./reports/01-rps/emmett-01.csv" using 9 w l
