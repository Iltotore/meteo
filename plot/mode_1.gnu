#!/usr/bin/gnuplot --persist

set term png
set output ARG2

set datafile separator ";"
set title "Min/Max/Average ".ARG3." by station"
set border 4095 front lt black linewidth 1.000 dashtype solid
set xlabel "Station" 
set ylabel ARG3

set xtics rotate by 90 right

Shadecolor = "#80E0A080"

plot ARG1 using 0:3:4:xticlabels(1) with filledcurve fc rgb Shadecolor title "Min and max", \
  '' using 0:2:xticlabels(1) smooth mcspline lw 2 title "Average"