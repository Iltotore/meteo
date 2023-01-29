#!/usr/bin/gnuplot -persist

set datafile separator ";"
set title ARG2." by day"

set border 4095 front lt black linewidth 1.000 dashtype solid
set palette maxcolors ARG3

set xlabel "Day"
set ylabel ARG2." per station per hour"
set cblabel "Station ID"

set xdata time
set timefmt "%s"
set format x "%y-%m-%d"

plot for [h=0:23] ARG1 using 2:(column(3+h)):1 with li palette notitle