#!/usr/bin/gnuplot -persist

set pm3d implicit at b

set term png
set output ARG2

set datafile separator ";"
set title "Moisture by station"
set border 4095 front lt black linewidth 1.000 dashtype solid
set xlabel "Latitude"
set ylabel "Longitude"
set cblabel "Moisture"

set view map
set pm3d interpolate 0,0
set hidden3d
set dgrid3d 50,50

set palette color positive

stats ARG1 using 2:3
splot [STATS_min_x:STATS_max_x][STATS_min_y:STATS_max_y] ARG1 using 2:3:4 with lines title ""