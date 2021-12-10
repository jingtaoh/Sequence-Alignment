# CSCI570_Final_Project
The project is the c++ implementation of the two different solutions provided in chapter 6 of the Kleinberg textbook for the Sequence Alignment problem (see [project description](CSCI570_Fall2021_FinalProject.pdf)).
- [x] [Basic](src/basic.cpp) implementation
- [x] [Memory efficient](src/efficient.cpp) implementation
- [x] Shell scripts
- [x] [Graphs](graphs)
- [x] [Summary](summary.txt)

## Compile & Run
```bash
# Compile and run basic program
./1942568982_2697735160_basic.sh

# Compile and run efficient program
./1942568982_2697735160_efficient.sh
```
## Measure time & memory performance
```bash
# Measure programs and write metrics into the corresponding output files
# %e - Elapsed real time (in seconds).
# %M - Maximum resident set size of the process during its lifetime (in Kbytes).

# Measure basic program
/usr/bin/time -a -f "%e\n%M" -o ../data/output_basic.txt ./basic ../data/input.txt

# Measure efficient program
/usr/bin/time -a -f "%e\n%M" -o ../data/output_efficient.txt ./efficient ../data/input.txt
```
## Graphs
```bash
gnuplot --persist ../graphs/time_plot.p
```
![CPU time plot](graphs/CPUPlot.png)
```bash
gnuplot --persist ../graphs/memory_plot.p
```
![Memory usage plot](graphs/MemoryPlot.png)

## Note  
> The optimal table is unique but the optimal alignment is not unique
