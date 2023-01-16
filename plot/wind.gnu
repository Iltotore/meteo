#!/usr/bin/gnuplot -persist

set datafile separator ";"
set title "Wind direction and speed"
set border 4095 front lt black linewidth 1.000 dashtype solid
set xlabel "Longitude" 
set xrange [ -180 : 180 ] noreverse nowriteback
set ylabel "Latitude" 
set yrange [ -85 : 85 ] noreverse nowriteback

plot "/dev/stdin" using 1:2:3:4 with vectors title "Wind vector"