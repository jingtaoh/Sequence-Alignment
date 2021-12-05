# Gnuplot script file for plotting data in file "basic.dat", "efficient.dat"
# This file is called time_plot.p
set logscale x 2
unset label                            # remove any previous labels
set xtic auto nomirror                   # set xtics automatically
set ytic auto nomirror                 # set ytics automatically
set title "Graph #1 CPU Time Plot" font ",12"
set xlabel "Problem Size" font ",12"
set ylabel "CPU Time (seconds)" font ",12"
set key font ",11"
plot    "../data/basic.dat" using 1:2 t 'basic' w lp lw 2 lt rgb "#F44336", \
        "../data/efficient.dat" using 1:2 t 'efficient' w lp lw 2 lt rgb "#8CC24A"