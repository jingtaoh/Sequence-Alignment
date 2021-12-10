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