#!/usr/bin/gnuplot -persist

set term png
set output ARG2

set datafile separator ";"
set title ARG3." by day"

set border 4095 front lt black linewidth 1.000 dashtype solid
set palette maxcolors ARG3

set xlabel "Day"
set ylabel ARG3." per station per hour"
set cblabel "Hour"
set cbrange [0:23]

set xdata time
set timefmt "%s"
set format x "%y-%m-%d"

plot for [h=0:23] ARG1 using 2:(column(3+h)):(column(3+h)) with li palette notitle