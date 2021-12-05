# Gnuplot script file for plotting data in file "basic.dat", "efficient.dat"
# This file is called memory_plot.p
set logscale x 2
unset label                            # remove any previous labels
set xtic auto nomirror                   # set xtics automatically
set ytic auto nomirror                 # set ytics automatically
set title "Graph #2 Memory Plot" font ",12"
set xlabel "Problem Size" font ",12"
set ylabel "Memory (kbs)" font ",12"
set key font ",11"
plot    "../graphs/basic.dat" using 1:3 t 'basic' w lp lw 2 lt rgb "#F44336", \
        "../graphs/efficient.dat" using 1:3 t 'efficient' w lp lw 2 lt rgb "#8CC24A"