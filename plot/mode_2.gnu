#!/usr/bin/gnuplot -persist

set datafile separator ";"
set title "Average ".ARG2." by time"
set border 4095 front lt black linewidth 1.000 dashtype solid
set xlabel "Time" 
set ylabel "Average ".ARG2

set xdata time
set timefmt "%s"

plot ARG1 using 1:2 with li title ARG2