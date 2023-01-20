#!/usr/bin/gnuplot -persist

set pm3d implicit at b

set datafile separator ";"
set title "Moisture by station"
set border 4095 front lt black linewidth 1.000 dashtype solid
set xlabel "Longitude" 
set ylabel "Latitude" 
set cblabel "Moisture"

set view map
set pm3d interpolate 0,0
set hidden3d
set dgrid3d 50,50

set palette color positive

stats ARG1 using 1:2
splot [STATS_min_x:STATS_max_x][STATS_min_y:STATS_max_y] ARG1 with lines