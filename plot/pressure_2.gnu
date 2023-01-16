#!/usr/bin/gnuplot -persist

set datafile separator ";"
set title "Average pressure by time"
set border 4095 front lt black linewidth 1.000 dashtype solid
set xlabel "Time" 
set ylabel "Average pressure"

set xdata time
set timefmt "%s"

plot "/dev/stdin" using 1:2 with li title "Pressure"

