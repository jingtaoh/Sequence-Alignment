BUILD_DIR="new_build"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir $BUILD_DIR
fi
cd $BUILD_DIR

# Compile
cmake ..
cmake --build .

# Run program
# output: ../data/output_basic.txt
./basic ../data/input.txt