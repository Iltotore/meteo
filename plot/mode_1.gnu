#!/usr/bin/gnuplot --persist

set datafile separator ";"
set title "Min/Max/Average ".ARG2." by station"
set border 4095 front lt black linewidth 1.000 dashtype solid
set xlabel "Station" 
set ylabel ARG2

Shadecolor = "#80E0A080"

plot ARG1 using 1:3:4 with filledcurve fc rgb Shadecolor title "Min and max", \
  '' using 1:2 smooth mcspline lw 2 title "Average"