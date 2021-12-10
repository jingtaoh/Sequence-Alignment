BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir $BUILD_DIR
fi
cd $BUILD_DIR

# Compile
cmake ..
cmake --build . --target efficient

# Run
# output: ../data/output_efficient.txt
./efficient ../data/input.txt

# To output with time and memory, comment the line above and uncomment the line below
# /usr/bin/time -a -f "%e\n%M" -o ../data/output_efficient.txt ./efficient ../data/input.txt
