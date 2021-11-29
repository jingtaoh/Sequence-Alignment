# CSCI570_Final_Project

## Compile & Run
```bash
# Compile
cd build  
cmake ..  
make  

# Run basic program
./basic ../data/input.txt

# Run efficient program
./efficient ../data/input.txt
```
## Measure time & memory performance
```bash
# Measure programs and write metrics into the corresponding output files
# %e - Elapsed real time (in seconds).
# %M - Maximum resident set size of the process during its lifetime (in Kbytes).

# Measure basic program
/usr/bin/time  -a -f "%e\n%M" -o ../data/output_basic.txt ./basic ../data/input.txt

# Measure efficient program
/usr/bin/time  -a -f "%e\n%M" -o ../data/output_efficient.txt ./efficient ../data/input.txt
```

## Note  
> The optimal table is unique but the optimal alignment is not unique
