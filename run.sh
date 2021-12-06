BUILD_DIR="new_build"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir $BUILD_DIR
fi
cd $BUILD_DIR

# Compile
cmake ..
make

# Run basic program
# output: ../data/output_basic.txt
./basic ../data/input.txt

# Run efficient program
# output: ../data/output_efficient.txt
./efficient ../data/input.txt